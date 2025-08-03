// Engine3D.cpp : Defines the entry point for the application.
//

#include "Engine3D.h"
#include "Core/Buffer.h"
#include "Core/Camera.h"
#include "Debugger/DebugLogger.h"
#include "Geometry/Mesh.h"
#include "Geometry/Model.h"
#include "Math/Math.h"
#include "Pipeline/Pipeline.h"
#include "Render/Render.h"
#include "Scene/Scene.h"
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <windows.h>
using namespace std;
#define WIDTH 200
#define HEIGHT 70

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

  // Ẩn con trỏ
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
  Render render = Render(WIDTH, HEIGHT);

  hide_cursor();
  Mesh cube = Mesh::createCube(12, 12, 12);
  Model model(&cube);
  Model model1(&cube);

  render.loadFromModel(model);
  render.loadFromModel(model1);

  Camera cam =
      Camera(Vec3(0, 0, 50), 0, 0, 15.0f, 100.0f, -12.0f, 12.0f, -12.0f, 12.0f);

  model.position = Vec3(10, 0, 26);
  model.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);
  model1.position = Vec3(20, 0, 20);
  model1.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);

  Scene scene;
  scene.camera = &cam;
  scene.addModel(&model);
  scene.addModel(&model1);
  render.scene = scene;

  // scene :: camera + model
  // buffer :: vbo + ibo

  while (true) {
    if (_kbhit()) {
      char ch = _getch();

      if (ch == 'l') {
        scene.models[0]->position = scene.models[0]->position + Vec3(1, 0, 0);
      }
      if (ch == 'j') {
        scene.models[0]->position = scene.models[0]->position + Vec3(-1, 0, 0);
      }
      if (ch == 'i') {
        scene.models[0]->position = scene.models[0]->position + Vec3(0, 1, 0);
      }

      if (ch == 'k') {
        scene.models[0]->position = scene.models[0]->position + Vec3(0, -1, 0);
      }

      if (ch == 'o') {
        scene.models[0]->position = scene.models[0]->position + Vec3(0, 0, 1);
      }
      if (ch == 'u') {
        scene.models[0]->position = scene.models[0]->position + Vec3(0, 0, -1);
      }

      if (ch == 's') {
        render.scene.camera->pitch = render.scene.camera->pitch - 3.14 / 100;
      }
      if (ch == 'w') {
        render.scene.camera->pitch = render.scene.camera->pitch + 3.14 / 100;
      }
      if (ch == 'd') {
        render.scene.camera->yaw = render.scene.camera->yaw - 3.14 / 100;
      }
      if (ch == 'a') {
        render.scene.camera->yaw = render.scene.camera->yaw + 3.14 / 100;
      }
      if (ch == 'h') {
        render.scene.camera->pos = render.scene.camera->pos + Vec3(1, 0, 0);
      }
      if (ch == 'f') {
        render.scene.camera->pos = render.scene.camera->pos + Vec3(-1, 0, 0);
      }
      if (ch == 't') {
        render.scene.camera->pos = render.scene.camera->pos + Vec3(0, 1, 0);
      }
      if (ch == 'g') {
        render.scene.camera->pos = render.scene.camera->pos + Vec3(0, -1, 0);
      }
      if (ch == 'y') {
        render.scene.camera->pos = render.scene.camera->pos + Vec3(0, 0, 1);
      }
      if (ch == 'r') {
        render.scene.camera->pos = render.scene.camera->pos + Vec3(0, 0, -1);
      }
    }
    // render.scene.camera->camAngle =
    //  render.scene.camera->camAngle + Vec3(-3.14 / 100, 0, 0);
    render.scene.models[0]->rotation =
        render.scene.models[0]->rotation +
        (Vec3(3.14 / 100, 3.14 / 100, 3.14 / 100));
    render.scene.models[1]->rotation =
        render.scene.models[0]->rotation +
        (Vec3(3.14 / 200, 3.14 / 200, 3.14 / 200));

    setColor(5, 0);
    render.present();
    Sleep(64);
  }

  return 0;
}
