#include "Game.h"
#include <conio.h>
#define WIDTH 300
#define HEIGHT 105
Game::Game() { init(); }

Game::~Game() = default;

/**
 * @brief Khởi tạo ban đầu cho camera, world, player
 */
void Game::init() {
  //khởi tạo game renderer
  gameRender = GameRender(WIDTH, HEIGHT);

  // khởi tạo camera, load vào game renderer, player trỏ tới
  cam = Camera(Vec3(0, 0, 20), 0, 0, 0.5f, 100.0f,
               (float(WIDTH) / float(HEIGHT)) * 0.5, 3.14 / 3);
  gameRender.renderer.scene.camera = &cam;
  player.init(&cam);

  // khổi tạo world , load vào game render
  world = World(8, 3, 8);
  world.init();
  world.setBlock(3, 2, 3, BlockType::STONE);
  world.setBlock(3, 1, 3, BlockType::STONE);
  world.setBlock(5, 1, 5, BlockType::STONE);
  gameRender.world = &world;

  // khởi tạo voxel grid, sinh mesh của world, sinh ra model của worlf, đẩy vào game render
  VoxelGrid grid(16, 16, 16);
  grid.loadGridFromWord(gameRender.world);
  Mesh::buildMesh(grid, gameRender.nWorld);
  model = Model(Vec3(0, 0, 0), &gameRender.nWorld);
  gameRender.renderer.loadFromModel(model);
  gameRender.renderer.scene.addModel(&model);
}

void Game::updateLogic() {
  if (_kbhit()) {
    char ch = _getch();
    auto *scene = &gameRender.renderer.scene;
    if (ch == 's') {
      player.rotationView(Vec3(-3.14 / 100, 0, 0));
    }
    if (ch == 'w') {
      player.rotationView(Vec3(3.14 / 100, 0, 0));
    }
    if (ch == 'd') {
      player.rotationView(Vec3(0, -3.14 / 100, 0));
    }
    if (ch == 'a') {
      player.rotationView(Vec3(0, 3.14 / 100, 0));
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
    if (ch == 'y') {
      player.move(UP);
    }
    if (ch == 'r') {
      player.move(DOWN);
    }
  }
}

void Game::updateRender() { gameRender.renderer.present(); }
