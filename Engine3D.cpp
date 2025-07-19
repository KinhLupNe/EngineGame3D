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
#include <windows.h>
using namespace std;

void gotoXY(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
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
  Camera cam = Camera(Vec3(0, 0, -5), Vec3(0, 0, 0), Vec3(0, 1, 0), 15, 35, -10,
                      10, 10, -10);
  Scene scene;
  scene.camera = &cam;
  scene.addModel(&model);
  Pipeline p;
  for (size_t i = 0; i < ibo.getSize(); i++) {

    Vec4 a = Vec4(vbo[ibo[i]].positon.x, vbo[ibo[i]].positon.y,
                  vbo[ibo[i]].positon.z, 1);

    Vec4 b = p.vertexShader(a, scene.models[0]->getWorldMatrix(),
                            scene.camera->getViewMatrix(),
                            scene.camera->getProjectionMatrix());

    Vec3 res = p.toScreen(100, 50, b);
    gotoXY((int)res.x, (int)res.y);
    cout << "#";
    /*cout << "X:" << vbo[ibo[i]].positon.x << " Y:" << vbo[ibo[i]].positon.y
         << " Z:" << vbo[ibo[i]].positon.z << endl;
    cout << "X':" << a.x << " Y':" << a.y << " Z':" << a.z << endl;*/
  }
  cout << endl;
  system("pause");
  return 0;
}
