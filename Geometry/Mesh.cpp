#include "Mesh.h"
#include "Vertex.h"

Mesh::Mesh() = default;
Mesh Mesh::createTriangle(Vec3 a, Vec3 b, Vec3 c) {
  Mesh m;
  m.vertices = {Vertex(a, Vec3(0, 0, 0)), Vertex(b, Vec3(0, 0, 0)),
                Vertex(c, Vec3(0, 0, 0))};
  m.indices = {0, 1, 2};
  return m;
}

Mesh Mesh::createCube(float const &w, float const &h, float const &l) {
  Mesh m;
  Vec3 t[8] = {{-w / 2, -h / 2, -l / 2}, {w / 2, -h / 2, -l / 2},

               {w / 2, -h / 2, l / 2},   {-w / 2, -h / 2, l / 2},
               {-w / 2, h / 2, -l / 2},  {w / 2, h / 2, -l / 2},

               {w / 2, h / 2, l / 2},    {-w / 2, h / 2, l / 2}};

  for (int i = 0; i < 8; i++) {
    m.vertices.push_back(Vertex(t[i], Vec3(0, 0, 0)));
  }
  m.indices = {0, 1, 2, 0, 2, 3, 0, 3, 7, 0, 7, 4, 0, 4, 5, 0, 5, 1,
               6, 4, 7, 6, 5, 4, 6, 7, 3, 6, 3, 2, 6, 2, 1, 6, 1, 5};
  return m;
}
Mesh::~Mesh() = default;
