#include "Game.h"
#include <conio.h>
#define WIDTH 200
#define HEIGHT 70
Game::Game() { init(); }
Game::~Game() = default;

void Game::init() {
  gameRender = GameRender(WIDTH, HEIGHT);
  cam = Camera(Vec3(0, 0, 20), 0, 0, 0.5f, 100.0f,
               (float(WIDTH) / float(HEIGHT)) * 0.5f, 3.14 / 3);
  gameRender.renderer.scene.camera = &cam;
  //----------------
  world = World(8, 3, 8);
  world.init();
  world.setBlock(10, 1, 10, BlockType::STONE);
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
  //  load vào trong vbos, ibos;
  gameRender.renderer.loadFromModel(model);
  gameRender.renderer.scene.addModel(&model);
}

void Game::updateLogic() {
  if (_kbhit()) {
    char ch = _getch();
    /*
          if (ch == 'l') {
            scene.models[0]->position = scene.models[0]->position + Vec3(1,
       0, 0);
          }
          if (ch == 'j') {
            scene.models[0]->position = scene.models[0]->position + Vec3(-1,
       0, 0);
          }
          if (ch == 'i') {
            scene.models[0]->position = scene.models[0]->position + Vec3(0,
       1, 0);
          }

          if (ch == 'k') {
            scene.models[0]->position = scene.models[0]->position + Vec3(0,
       -1, 0);
          }

          if (ch == 'o') {
            scene.models[0]->position = scene.models[0]->position + Vec3(0,
       0, 1);
          }
          if (ch == 'u') {
            scene.models[0]->position = scene.models[0]->position + Vec3(0,
       0, -1);
          }*/
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
      player.move(Vec3(0.2, 0, 0));
    }
    if (ch == 'f') {
      player.move(Vec3(-0.2, 0, 0));
    }
    if (ch == 't') {
      player.move(Vec3(0, 0, -0.2));
    }
    if (ch == 'g') {
      player.move(Vec3(0, 0, 0.2));
    }
    if (ch == 'y') {
      player.move(Vec3(0, 0.2, 0));
    }
    if (ch == 'r') {
      player.move(Vec3(0, -0.2, 0));
    }
  }
}

void Game::updateRender() { gameRender.renderer.present(); }
