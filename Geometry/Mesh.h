#ifndef MESH_H
#define MESH_H
#include "Vertex.h"
#include <vector>
class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;

  static Mesh createTriangle(Vec3 a, Vec3 b, Vec3 c);
  // static Mesh createRectangle();
  static Mesh createCube(float const &w, float const &h, float const &l);
  Mesh();
  ~Mesh();
};
#endif
