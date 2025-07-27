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
#include <vector>
#include <windows.h>
using namespace std;
#define WIDTH 300
#define HEIGHT 90

char buf[HEIGHT][WIDTH];

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
  Buffer buffer;
  IndexBuffer ibo;
  VertexBuffer vbo;
  Pipeline p;

  buffer.loadFromMesh(cube);
  ibo = buffer.getIBO();
  vbo = buffer.getVBO();

  Camera cam = Camera(Vec3(0, 0, -5), Vec3(0, 0, 0), Vec3(0, 1, 0), 15, 45, -12,
                      12, 12, -12);
  Scene scene;
  scene.camera = &cam;

  model.position = Vec3(10, 0, 26);
  model.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);
  scene.addModel(&model);

  vector<Vec4> clipVers;
  while (true) {
    memset(buf, ' ', sizeof(buf));
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

    model.rotation = model.rotation + Vec3(3.14 / 80, 3.14 / 80, 3.14 / 80);

    /*for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
     cout << model.getWorldMatrix().m[i][j] << " ";
   }
   cout << endl;
 }*/
    clipVers.clear();
    for (size_t i = 0; i < vbo.getSize(); i++) {
      Vec4 a = Vec4(vbo[i].positon.x, vbo[i].positon.y, vbo[i].positon.z, 1);

      Vec4 b = p.vertexShader(a, scene.models[0]->getWorldMatrix(),
                              scene.camera->getViewMatrix(),
                              scene.camera->getProjectionMatrix());

      clipVers.push_back(b);

      /*cout << "X:" << vbo[ibo[i]].positon.x << " Y:" << vbo[ibo[i]].positon.y
           << " Z:" << vbo[ibo[i]].positon.z << endl;
      cout << "X':" << a.x << " Y':" << a.y << " Z':" << a.z << endl;*/
    }
    /*
      int k = 0;
      for (auto i : clipVers) {
        cout << k++ << ": " << i.x << ", " << i.y << ", " << i.z << ", " << i.w
             << endl;
      }
    */
    vector<Triangle> tris = p.assemble(clipVers, ibo.data);
    /*for (int i = 0; i < tris.size(); i++) {
      cout << i << endl;
      cout << "x:" << tris[i].v0.x << "y:" << tris[i].v0.x << "z:" <<
    tris[i].v0.z
           << "w: " << tris[i].v0.w << endl;
      // cout << ibo.data[i] << ", ";
      cout << "x:" << tris[i].v1.x << "y:" << tris[i].v1.x << "z:" <<
    tris[i].v1.z
           << "w: " << tris[i].v1.w << endl;
      cout << "x:" << tris[i].v2.x << "y:" << tris[i].v2.x << "z:" <<
    tris[i].v2.z
           << "w: " << tris[i].v2.w << endl;
      //
    }*/

    // for (int i = 0; i <= WIDTH; i++) {
    // gotoXY(i, 0);
    // cout << "#";
    // gotoXY(i, HEIGHT);
    // cout << "#";
    //}
    // for (int i = 0; i <= HEIGHT; i++) {
    // gotoXY(0, i);
    // cout << "#";
    // gotoXY(WIDTH, i);
    // cout << "#";
    //}

    for (auto &i : tris) {
      if (p.backFaceCull(i) == true) {
        // cout << "x: " << i.v0.x << "y:" << i.v0.y << "z: " << i.v0.z
        // << "w:" << i.v0.w << endl;

        vector<Triangle> temp = p.primitiveClipping(i);
        gotoXY(120, 20);
        // cout << "So tam giac sau khi cat :" << temp.size();
        for (auto &i : temp) {

          Vec3 res0 = p.toScreen(WIDTH, HEIGHT, i.v0);

          Vec3 res1 = p.toScreen(WIDTH, HEIGHT, i.v1);

          Vec3 res2 = p.toScreen(WIDTH, HEIGHT, i.v2);
          setColor(7, 0);
          // cout << res0.z << endl;
          vector<Vec3> tt = p.rasterization(res0, res1, res2);
          for (auto j : tt) {
            char ex;
            // cout << j.z << endl;
            if (j.z >= 0.8)
              ex = '@';
            if (j.z < 0.8 && j.z >= 0.7)
              ex = '#';
            if (j.z < 0.7 && j.z >= 0.6)
              ex = '+';
            if (j.z < 0.6 && j.z >= 0.5)
              ex = ':';
            if (j.z < 0.5)
              ex = '.';
            buf[(int)j.y][(int)j.x] = ex;
            // gotoXY((int)j.x, (int)j.y);
            // cout << "#";
          }

          /*setColor(2, 0);
          vector<Vec2> t = getLinePoints(res0, res1);
          for (auto j : t) {
            gotoXY((int)j.x, (int)j.y);
            cout << "";
          }

          t = getLinePoints(res1, res2);
          for (auto j : t) {
            gotoXY((int)j.x, (int)j.y);
            cout << "#";
          }

          t = getLinePoints(res2, res0);
          for (auto j : t) {
            gotoXY((int)j.x, (int)j.y);
            cout << "#";
          }
          */
        }

        // cout << "x :" << res0.x << "y: " << res0.y << "z:" << res0.z << endl;
        // cout << "x :" << res1.x << "y: " << res1.y << "z:" << res1.z << endl;
        // cout << "x :" << res2.x << "y: " << res2.y << "z:" << res2.z << endl;
      }
    }
    // Vec3 res = p.toScreen(100, 50, b);
    //  gotoXY((int)res.x, (int)res.y);
    // cout << "#";
    std::string frame = build_frame();
    std::cout << "\x1b[H" << frame << std::flush;

    // cout << endl;
    Sleep(32);
  }
  return 0;
}
