// Engine3D.cpp : Defines the entry point for the application.
//

#include "Engine3D.h"
#include "Core/Buffer.h"
#include "Core/Camera.h"
#include "Debugger/DebugLogger.h"
#include "Game/GameRender/GameRender.h"
#include "Game/World/World.h"
#include "Geometry/Mesh.h"
#include "Geometry/Model.h"
#include "Math/Math.h"
#include "Pipeline/Pipeline.h"
#include "Render/Render.h"
#include "Scene/Scene.h"
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <random>
#include <vector>
#include <windows.h>
using namespace std;
#define WIDTH 300
#define HEIGHT 105

#include <cstdlib>
#include <fstream>

char buf[HEIGHT][WIDTH];
float zbuf[HEIGHT][WIDTH];
void resetZbuffer() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      zbuf[i][j] = 100.0f;
    }
  }
}
void gotoXY(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setColor(int textColor, int bgColor) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void hide_cursor() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;

  // Lấy thông tin hiện tại của con trỏ
  GetConsoleCursorInfo(hConsole, &cursorInfo);

  // Ẩn con tr
  cursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo(hConsole, &cursorInfo);
}

std::string build_frame() {
  std::string frame;
  frame.reserve(HEIGHT * (WIDTH + 1));
  for (int i = 0; i < HEIGHT; i++) {
    frame.append(buf[i], WIDTH);
    frame.push_back('\n');
  }
  return frame;
}

int main() {
  // Render render = Render(WIDTH, HEIGHT);
  GameRender gameRender = GameRender(WIDTH, HEIGHT);

  Camera cam = Camera(Vec3(0, 0, 8), 0, 0, 0.5f, 100.0f,
                      (float(WIDTH) / float(HEIGHT)) * 0.5f, 3.14 / 3);
  gameRender.renderer.scene.camera = &cam;
  World world = World(2, 1, 2);
  world.init();
  gameRender.drawWorld(world);

  hide_cursor();
  /*Mesh cube = Mesh::createCube(1, 1, 1);
  Model model(&cube);
  Model model1(&cube);

  render.loadFromModel(model);
  render.loadFromModel(model1);

  Camera cam = Camera(Vec3(0, 0, 50), 0, 0, 0.1f, 100.0f,
                      (float(WIDTH) / float(HEIGHT)) * 0.5f, 3.14 / 3);

  model.position = Vec3(10, 0, 10);
  //  model.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);
  model1.position = Vec3(25, 5, 15);
  model1.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);

  Scene scene;
  scene.camera = &cam;
  scene.addModel(&model);
  scene.addModel(&model1);
  render.scene = scene;
*/
  // scene :: camera + model
  // buffer :: vbo + ibo

  while (true) {
    if (_kbhit()) {
      char ch = _getch();
      /*
            if (ch == 'l') {
              scene.models[0]->position = scene.models[0]->position + Vec3(1, 0,
         0);
            }
            if (ch == 'j') {
              scene.models[0]->position = scene.models[0]->position + Vec3(-1,
         0, 0);
            }
            if (ch == 'i') {
              scene.models[0]->position = scene.models[0]->position + Vec3(0, 1,
         0);
            }

            if (ch == 'k') {
              scene.models[0]->position = scene.models[0]->position + Vec3(0,
         -1, 0);
            }

            if (ch == 'o') {
              scene.models[0]->position = scene.models[0]->position + Vec3(0, 0,
         1);
            }
            if (ch == 'u') {
              scene.models[0]->position = scene.models[0]->position + Vec3(0, 0,
         -1);
            }*/

      if (ch == 's') {
        gameRender.renderer.scene.camera->pitch =
            gameRender.renderer.scene.camera->pitch - 3.14 / 100;
      }
      if (ch == 'w') {
        gameRender.renderer.scene.camera->pitch =
            gameRender.renderer.scene.camera->pitch + 3.14 / 100;
      }
      if (ch == 'd') {
        gameRender.renderer.scene.camera->yaw =
            gameRender.renderer.scene.camera->yaw - 3.14 / 100;
      }
      if (ch == 'a') {
        gameRender.renderer.scene.camera->yaw =
            gameRender.renderer.scene.camera->yaw + 3.14 / 100;
      }
      if (ch == 'h') {
        gameRender.renderer.scene.camera->pos =
            gameRender.renderer.scene.camera->pos + Vec3(0.2, 0, 0);
      }
      if (ch == 'f') {
        gameRender.renderer.scene.camera->pos =
            gameRender.renderer.scene.camera->pos + Vec3(-0.2, 0, 0);
      }
      if (ch == 't') {
        gameRender.renderer.scene.camera->pos =
            gameRender.renderer.scene.camera->pos + Vec3(0, 0.2, 0);
      }
      if (ch == 'g') {
        gameRender.renderer.scene.camera->pos =
            gameRender.renderer.scene.camera->pos + Vec3(0, -0.2, 0);
      }
      if (ch == 'y') {
        gameRender.renderer.scene.camera->pos =
            gameRender.renderer.scene.camera->pos + Vec3(0, 0, 0.2);
      }
      if (ch == 'r') {
        gameRender.renderer.scene.camera->pos =
            gameRender.renderer.scene.camera->pos + Vec3(0, 0, -0.2);
      }
    }
    // render.scene.camera->camAngle =
    //  render.scene.camera->camAngle + Vec3(-3.14 / 100, 0, 0);
    // render.scene.models[0]->rotation =
    //  render.scene.models[0]->rotation +
    //(Vec3(3.14 / 100, 3.14 / 100, 3.14 / 100));
    /*render.scene.models[1]->rotation =
        render.scene.models[0]->rotation +
        (Vec3(3.14 / 200, 3.14 / 200, 3.14 / 200));*/

    setColor(5, 0);
    gameRender.renderer.present();
    Sleep(64);
  }

  return 0;
}
