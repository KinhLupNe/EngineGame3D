// Engine3D.cpp : Defines the entry point for the application.
//

#include "Engine3D.h"
#include "Core/Buffer.h"
#include "Core/Camera.h"
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
#define HEIGHT 80

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
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      buf[i][j] = ' ';
    }
  }
  hide_cursor();
  Mesh cube = Mesh::createCube(12, 12, 12);
  Model model(&cube);
  Model model1(&cube);
  Buffer buffer, buffer1;
  IndexBuffer ibo, ibo1;
  VertexBuffer vbo, vbo1;
  Pipeline p;

  buffer.loadFromMesh(cube);
  ibo = buffer.getIBO();
  vbo = buffer.getVBO();
  buffer1.loadFromMesh(cube);
  ibo1 = buffer1.getIBO();
  vbo1 = buffer1.getVBO();
  Camera cam = Camera(Vec3(0, 0, -5), Vec3(0, 0, 0), Vec3(0, 1, 0), 15, 45, -12,
                      12, 12, -12);
  Scene scene;
  scene.camera = &cam;

  model.position = Vec3(10, 0, 26);
  model.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);
  model1.position = Vec3(10, 0, 26);
  model1.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);

  scene.addModel(&model);
  scene.addModel(&model1);

  vector<Vec4> clipVers;
  while (true) {
    memset(buf, ' ', sizeof(buf));
    resetZbuffer();
    // memset(zbuf, 1000, sizeof(zbuf));
    if (_kbhit()) {
      char ch = _getch();
      if (ch == 'a') {
        scene.models[0]->position = scene.models[0]->position + Vec3(1, 0, 0);
      }
      if (ch == 's')
        model.position = model.position + Vec3(0, 1, 0);
      if (ch == 'd')
        model.position = model.position + Vec3(-1, 0, 0);

      if (ch == 'w')
        model.position = model.position + Vec3(0, -1, 0);

      if (ch == 'z')
        model.position = model.position + Vec3(0, 0, 1);

      if (ch == 'c')
        model.position = model.position + Vec3(0, 0, -1);
    }

    model.rotation = model.rotation + Vec3(3.14 / 100, 3.14 / 100, 3.14 / 100);

    model1.rotation =
        model1.rotation + Vec3(3.14 / 200, 3.14 / 200, 3.14 / 200);
    clipVers.clear();
    for (size_t i = 0; i < vbo.getSize(); i++) {
      Vec4 a = Vec4(vbo[i].positon.x, vbo[i].positon.y, vbo[i].positon.z, 1);

      Vec4 b = p.vertexShader(a, scene.models[0]->getWorldMatrix(),
                              scene.camera->getViewMatrix(),
                              scene.camera->getProjectionMatrix());

      clipVers.push_back(b);
    }

    vector<Triangle> tris = p.assemble(clipVers, ibo.data);

    for (auto &i : tris) {
      if (p.backFaceCull(i) == true) {
        // cout << "x: " << i.v0.x << "y:" << i.v0.y << "z: " << i.v0.z
        // << "w:" << i.v0.w << endl;

        vector<Triangle> temp = p.primitiveClipping(i);
        // gotoXY(120, 20);
        //  cout << "So tam giac sau khi cat :" << temp.size();
        for (auto &i : temp) {

          Vec3 res0 = p.toScreen(WIDTH, HEIGHT, i.v0);

          Vec3 res1 = p.toScreen(WIDTH, HEIGHT, i.v1);

          Vec3 res2 = p.toScreen(WIDTH, HEIGHT, i.v2);
          // setColor(7, 0);
          // gotoXY(res0.x, res0.y);
          // cout << i.v0.z << " " << res0.z;
          // gotoXY(res1.x, res1.y);
          // cout << i.v1.z << " " << res1.z;
          // gotoXY(res2.x, res2.y);
          // cout << i.v2.z << " " << res2.z;
          // cout << res0.z << endl;
          vector<Vec3> tt = p.rasterization(res0, res1, res2, i);
          for (auto j : tt) {

            char ex = '@'; // mặc định tối nhất
            if (j.z >= 0.93f)
              ex = ' ';
            else if (j.z >= 0.86f)
              ex = '.';
            else if (j.z >= 0.79f)
              ex = ':';
            else if (j.z >= 0.72f)
              ex = ';';
            else if (j.z >= 0.65f)
              ex = '?';
            else if (j.z >= 0.58f)
              ex = '[';
            else if (j.z >= 0.51f)
              ex = 'f';
            else if (j.z >= 0.44f)
              ex = 'm';
            else if (j.z >= 0.37f)
              ex = '#';
            else if (j.z >= 0.30f)
              ex = '@';
            if (zbuf[(int)j.y][(int)j.x] > j.z) {
              zbuf[(int)j.y][(int)j.x] = j.z;
              buf[(int)j.y][(int)j.x] = ex;
            }
            // gotoXY((int)j.x, (int)j.y);
            // cout << "#";
          }
        }
      }
    }
    clipVers.clear();
    for (size_t i = 0; i < vbo1.getSize(); i++) {
      Vec4 a = Vec4(vbo1[i].positon.x, vbo1[i].positon.y, vbo1[i].positon.z, 1);

      Vec4 b = p.vertexShader(a, scene.models[1]->getWorldMatrix(),
                              scene.camera->getViewMatrix(),
                              scene.camera->getProjectionMatrix());

      clipVers.push_back(b);
    }

    tris = p.assemble(clipVers, ibo1.data);

    for (auto &i : tris) {
      if (p.backFaceCull(i) == true) {
        // cout << "x: " << i.v0.x << "y:" << i.v0.y << "z: " << i.v0.z
        // << "w:" << i.v0.w << endl;

        vector<Triangle> temp = p.primitiveClipping(i);
        // gotoXY(120, 20);
        //  cout << "So tam giac sau khi cat :" << temp.size();
        for (auto &i : temp) {

          Vec3 res0 = p.toScreen(WIDTH, HEIGHT, i.v0);

          Vec3 res1 = p.toScreen(WIDTH, HEIGHT, i.v1);

          Vec3 res2 = p.toScreen(WIDTH, HEIGHT, i.v2);
          // setColor(7, 0);
          // gotoXY(res0.x, res0.y);
          // cout << i.v0.z << " " << res0.z;
          // gotoXY(res1.x, res1.y);
          // cout << i.v1.z << " " << res1.z;
          // gotoXY(res2.x, res2.y);
          // cout << i.v2.z << " " << res2.z;
          // cout << res0.z << endl;
          vector<Vec3> tt = p.rasterization(res0, res1, res2, i);
          for (auto j : tt) {

            char ex = '@'; // mặc định tối nhất
            if (j.z >= 0.93f)
              ex = ' ';
            else if (j.z >= 0.86f)
              ex = '.';
            else if (j.z >= 0.79f)
              ex = ':';
            else if (j.z >= 0.72f)
              ex = ';';
            else if (j.z >= 0.65f)
              ex = '?';
            else if (j.z >= 0.58f)
              ex = '[';
            else if (j.z >= 0.51f)
              ex = 'f';
            else if (j.z >= 0.44f)
              ex = 'm';
            else if (j.z >= 0.37f)
              ex = '#';
            else if (j.z >= 0.30f)
              ex = '@';

            if (zbuf[(int)j.y][(int)j.x] > j.z) {
              zbuf[(int)j.y][(int)j.x] = j.z;
              buf[(int)j.y][(int)j.x] = ex;
            }

            // gotoXY((int)j.x, (int)j.y);
            // cout << "#";
          }
        }
      }
    }
    // Vec3 res = p.toScreen(100, 50, b);
    //  gotoXY((int)res.x, (int)res.y);
    // cout << "#";
    std::string frame = build_frame();
    std::cout << "\x1b[H" << frame << std::flush;

    // cout << endl;
    // system("pause");
    Sleep(32);
    // system("cls");
  }
  return 0;
}
