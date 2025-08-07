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
  // khởi tạo game renderer
  gameRender = GameRender(WIDTH, HEIGHT);

  // khởi tạo camera, load vào game renderer, player trỏ tới
  cam = Camera(Vec3(0, 0, 20), 0, 0, 0.5f, 100.0f,
               (static_cast<float>(WIDTH) / static_cast<float>(HEIGHT)) * 0.5,
               3.14 / 3);
  gameRender.getRenderer().getScene().set_camera(&cam);
  player.init(&cam);

  // khổi tạo world , load vào game render
  world = World(20, 7, 5);
  // world.init();
  // world.setBlock(0, 2, 3, BlockType::STONE);
  // H
  world.setBlock(0, 1, 3, BlockType::STONE);

  world.setBlock(0, 2, 3, BlockType::STONE);

  world.setBlock(0, 3, 3, BlockType::STONE);

  world.setBlock(0, 4, 3, BlockType::STONE);

  world.setBlock(0, 5, 3, BlockType::STONE);

  world.setBlock(1, 3, 3, BlockType::STONE);

  world.setBlock(2, 3, 3, BlockType::STONE);

  world.setBlock(3, 1, 3, BlockType::STONE);

  world.setBlock(3, 2, 3, BlockType::STONE);

  world.setBlock(3, 3, 3, BlockType::STONE);

  world.setBlock(3, 4, 3, BlockType::STONE);

  world.setBlock(3, 5, 3, BlockType::STONE);
  // U
  world.setBlock(5, 2, 3, BlockType::STONE);
  world.setBlock(5, 3, 3, BlockType::STONE);

  world.setBlock(5, 4, 3, BlockType::STONE);

  world.setBlock(5, 5, 3, BlockType::STONE);

  world.setBlock(6, 1, 3, BlockType::STONE);

  world.setBlock(7, 1, 3, BlockType::STONE);

  world.setBlock(8, 2, 3, BlockType::STONE);

  world.setBlock(8, 3, 3, BlockType::STONE);

  world.setBlock(8, 4, 3, BlockType::STONE);

  world.setBlock(8, 5, 3, BlockType::STONE);
  // S
  world.setBlock(10, 1, 3, BlockType::STONE);

  world.setBlock(10, 4, 3, BlockType::STONE);

  world.setBlock(11, 1, 3, BlockType::STONE);

  world.setBlock(11, 3, 3, BlockType::STONE);

  world.setBlock(11, 5, 3, BlockType::STONE);

  world.setBlock(12, 2, 3, BlockType::STONE);

  world.setBlock(12, 5, 3, BlockType::STONE);

  // T
  world.setBlock(14, 5, 3, BlockType::STONE);

  world.setBlock(15, 5, 3, BlockType::STONE);

  world.setBlock(16, 5, 3, BlockType::STONE);

  world.setBlock(15, 4, 3, BlockType::STONE);

  world.setBlock(15, 3, 3, BlockType::STONE);

  world.setBlock(15, 2, 3, BlockType::STONE);

  world.setBlock(15, 1, 3, BlockType::STONE);

  gameRender.setWorld(&world);

  // khởi tạo voxel grid, sinh mesh của world, sinh ra model của worlf, đẩy vào
  // game render
  VoxelGrid grid(20, 10, 16);
  grid.loadGridFromWord(gameRender.getWorld());
  Mesh::buildMesh(grid, gameRender.getNWorld());
  model = Model(Vec3(0, 0, 0), &gameRender.getNWorld());
  gameRender.getRenderer().loadFromModel(model);
  gameRender.getRenderer().getScene().addModel(&model);
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
    if (ch == ' ') {
      player.move(UP);
    }
    if (ch == 'e') {
      player.move(DOWN);
    }
  }
}

void Game::updateRender() { gameRender.getRenderer().present(); }
