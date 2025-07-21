// Engine3D.cpp : Defines the entry point for the application.
//

#include "Engine3D.h"
#include "Core/Buffer.h"
#include "Core/Camera.h"
#include "Geometry/Mesh.h"
#include "Geometry/Model.h"
#include "Math/Math.h"
#include "Pipeline/Pipeline.h"
#include "Scene/Scene.h"
#include <cstdlib>
#include <vector>
#include <windows.h>
using namespace std;

void gotoXY(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
int main() {
  hide_cursor();
  Mesh cube = Mesh::createCube(12, 12, 12);
  Model model(&cube);
  model.position = Vec3(0, 0, 26);
  model.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);
  Buffer buffer;
  buffer.loadFromMesh(cube);
  IndexBuffer ibo = buffer.getIBO();
  VertexBuffer vbo = buffer.getVBO();
  system("cls");

  /*for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << model.getWorldMatrix().m[i][j] << " ";
    }
    cout << endl;
  }*/
  Camera cam = Camera(Vec3(0, 0, -5), Vec3(0, 0, 0), Vec3(0, 1, 0), 15, 45, -12,
                      12, 12, -12);
  Scene scene;
  scene.camera = &cam;
  scene.addModel(&model);
  Pipeline p;

  vector<Vec4> clipVers;
  while (true) {
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

    for (int i = 0; i < 100; i++) {
      gotoXY(i, 0);
      cout << "#";
      gotoXY(i, 39);
      cout << "#";
    }
    for (int i = 0; i < 40; i++) {
      gotoXY(0, i);
      cout << "#";
      gotoXY(99, i);
      cout << "#";
    }
    for (auto &i : tris) {
      if (p.backFaceCull(i) == true) {
        // cout << "x: " << i.v0.x << "y:" << i.v0.y << "z: " << i.v0.z
        // << "w:" << i.v0.w << endl;
        Vec3 res0 = p.toScreen(100, 40, i.v0);

        Vec3 res1 = p.toScreen(100, 40, i.v1);

        Vec3 res2 = p.toScreen(100, 40, i.v2);

        gotoXY((int)res0.x, (int)res0.y);
        cout << "#";
        gotoXY((int)res1.x, (int)res1.y);
        cout << "#";
        gotoXY((int)res2.x, (int)res2.y);
        cout << "#";
        // cout << "x :" << res0.x << "y: " << res0.y << "z:" << res0.z << endl;
        // cout << "x :" << res1.x << "y: " << res1.y << "z:" << res1.z << endl;
        // cout << "x :" << res2.x << "y: " << res2.y << "z:" << res2.z << endl;
      }
    }
    // Vec3 res = p.toScreen(100, 50, b);
    //  gotoXY((int)res.x, (int)res.y);
    // cout << "#";
    cout << endl;
  }
  return 0;
}
