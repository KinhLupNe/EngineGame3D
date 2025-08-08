#include "Game.h"
#include "../World/Cube.h"
#include <conio.h>
#define WIDTH 300
#define HEIGHT 105
Game::Game() { init(); }

Game::~Game() = default;

/**
 * @brief Khởi tạo ban đầu cho Game
 */
void Game::init() {
  // khởi tạo game renderer
  gameRender = GameRender(WIDTH, HEIGHT);

  // khởi tạo camera, load vào game renderer, player
  cam = Camera(Vec3(0, 0, 20), 0, 0, 0.5f, 100.0f,
               (static_cast<float>(WIDTH) / static_cast<float>(HEIGHT)) * 0.5,
               3.14 / 3);
  gameRender.getRenderer().getScene().set_camera(&cam);
  player.init(&cam);

  // khổi tạo world , load vào game render
  world = World(20, 7, 5);
  // world.init();
  world.loadWorldFromFile("../../../Game/Soure/worldMap.txt");
  // khởi tạo voxel grid, sinh mesh của world(sinh model từ grid có thuật toán
  // neibor face-culling)
  VoxelGrid grid(20, 10, 16);
  grid.loadGridFromWorld(&world);
  Mesh mWorld;
  Mesh::buildMesh(grid, mWorld);

  // sinh model từ mesh của world
  models.emplace_back(Vec3(0, 0, 0), &mWorld);

  // model đối tượng thứ 2
  Mesh cubeMesh = Mesh::createCube(1.0f, 1.0f, 1.0f);
  Cube cube(Vec3(10, 8, 3), Vec3(1.5, 1.5, 1.5),
            Vec3(3.14 / 8, 3.14 / 10, 3.14 / 12), cubeMesh);
  models.emplace_back(cube);

  for (auto &model : models) {
    gameRender.loadModelToGame(model);
  }
}

void Game::updateLogic() {
  // TODO cần module input riêng biệt, xử lí các logic phưc tạp của vật thể
  // input
  if (_kbhit()) {
    char ch = _getch();
    if (ch == 's') {
      player.rotatePlayerView(LOOK_DOWN);
    }
    if (ch == 'w') {
      player.rotatePlayerView(LOOK_UP);
    }
    if (ch == 'd') {
      player.rotatePlayerView(LOOK_RIGHT);
    }
    if (ch == 'a') {
      player.rotatePlayerView(LOOK_LEFT);
    }
    if (ch == 'h') {
      player.move(RIGHT);
    }
    if (ch == 'f') {
      player.move(LEFT);
    }
    if (ch == 't') {
      player.move(AHEAD);
    }
    if (ch == 'g') {
      player.move(BACKWARD);
    }
    if (ch == ' ') {
      player.move(UP);
    }
    if (ch == 'e') {
      player.move(DOWN);
    }
  }
  // update logic//
  static float a = 0;
  a += 0.02f;
  if (a >= 6.28f) {
    a = 0;
  }
  this->models[1].rotation =
      this->models[1].rotation + Vec3(0.03f, 0.03f, 0.03f);

  this->models[1].position.x = 8 + cos(a) * 12;
  this->models[1].position.y = 3 + sin(a) * 8;
}

void Game::updateRender() { gameRender.getRenderer().present(); }
