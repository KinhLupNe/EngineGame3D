#include "Game.h"
#include <conio.h>
#define WIDTH 300
#define HEIGHT 105
Game::Game() { init(); }

Game::~Game() = default;

/**
 * @brief Khởi tạo ban đầu cho Game
 */
void Game::init() {
  //khởi tạo game renderer
  gameRender = GameRender(WIDTH, HEIGHT);

  // khởi tạo camera, load vào game renderer, player trỏ tới
  cam = Camera(Vec3(0, 0, 20), 0, 0, 0.5f, 100.0f,
               (static_cast<float>(WIDTH) / static_cast<float>(HEIGHT)) * 0.5, 3.14 / 3);
  gameRender.getRenderer().scene.camera = &cam;
  player.init(&cam);

  // khổi tạo world , load vào game render
  world = World(9, 7, 9);
  //world.init();
  world.setBlock(0, 2, 3, BlockType::STONE);
  world.setBlock(0, 3, 3, BlockType::STONE);
  world.setBlock(0, 4, 3, BlockType::STONE);
  world.setBlock(0, 5, 3, BlockType::STONE);
  world.setBlock(1, 4, 3, BlockType::STONE);
  world.setBlock(2, 3, 3, BlockType::STONE);
  world.setBlock(3, 4, 3, BlockType::STONE);
  world.setBlock(4, 5, 3, BlockType::STONE);
  world.setBlock(4, 4, 3, BlockType::STONE);
  world.setBlock(4, 3, 3, BlockType::STONE);
  world.setBlock(4, 2, 3, BlockType::STONE);
  world.setBlock(6, 2, 3, BlockType::STONE);
  world.setBlock(6, 3, 3, BlockType::STONE);
  world.setBlock(6, 5, 3, BlockType::STONE);


  gameRender.setWorld(&world);

  // khởi tạo voxel grid, sinh mesh của world, sinh ra model của worlf, đẩy vào game render
  VoxelGrid grid(16, 16, 16);
  grid.loadGridFromWord(gameRender.getWorld());
  Mesh::buildMesh(grid, gameRender.getNWorld());
  model = Model(Vec3(0, 0, 0), &gameRender.getNWorld());
  gameRender.getRenderer().loadFromModel(model);
  gameRender.getRenderer().scene.addModel(&model);
}

void Game::updateLogic() {
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
    if (ch == 'y') {
      player.move(UP);
    }
    if (ch == 'r') {
      player.move(DOWN);
    }
  }
}

void Game::updateRender() { gameRender.getRenderer().present(); }
