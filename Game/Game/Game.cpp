#include "Game.h"
#include <conio.h>
#define WIDTH 300
#define HEIGHT 105
Game::Game() { init(); }
Game::~Game() = default;

void Game::init() {
  gameRender = GameRender(WIDTH, HEIGHT);
  cam = Camera(Vec3(0, 0, 20), 0, 0, 0.5f, 100.0f,
               (float(WIDTH) / float(HEIGHT)) * 0.5, 3.14 / 3);
  gameRender.renderer.scene.camera = &cam;
  //----------------
  world = World(8, 3, 8);
  world.init();
  world.setBlock(3, 2, 3, BlockType::STONE);
  world.setBlock(3, 1, 3, BlockType::STONE);
  world.setBlock(5, 1, 5, BlockType::STONE);

  gameRender.world = &world;
  //----------------
  VoxelGrid grid(16, 16, 16);
  grid.loadGridFromWord(gameRender.world);
  Mesh::buildMesh(grid, gameRender.nWorld);
  //----------------
  model = Model(Vec3(0, 0, 0), &gameRender.nWorld);
  //------
  // player = Player();

  player.init(&cam);
  // test
  // cube1 = Mesh::createCube(1, 1, 1);
  // cube2 = Mesh::createCube(1, 1, 1);

  // model1 = Model(&cube1);
  // model2 = Model(&cube2);
  // model1.position = Vec3(3, 0, 3);
  // model2.position = Vec3(3, 1, 5);

  // load vào trong vbos, ibos;
  gameRender.renderer.loadFromModel(model);
  gameRender.renderer.scene.addModel(&model);
  // gameRender.renderer.loadFromModel(model1);
  // gameRender.renderer.scene.addModel(&model1);
  // gameRender.renderer.loadFromModel(model2);
  // gameRender.renderer.scene.addModel(&model2);
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
