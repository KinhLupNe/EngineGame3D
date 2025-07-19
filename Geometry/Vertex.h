#ifndef VERTEX_H
#define VERTEX_H
#include "../Math/Math.h"
#include <cstdint>
struct Vertex {
  Vec3 positon;
  Vec3 normalize;

  Vertex(Vec3 p, Vec3 n) : positon(p), normalize(n) {}
};
#endif
