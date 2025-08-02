#ifndef VERTEX_H
#define VERTEX_H
#include "../Math/Math.h"
#include <cstdint>
struct VertexOutput {
  Vec3 posView;   // position in view space
  Vec4 posClip;   // position in clip space
  Vec3 posScreen; // position in screen space
  Vec3 normal;    // normal in world space
  Vec3 color;     // color in world space
};
// Tam giác trong không gian clip
struct TriangleOutput {
  VertexOutput v0; // vertex 0 in clip space
  VertexOutput v1; // vertex 1 in clip space
  VertexOutput v2; // vertex 2 in clip space
};
struct Vertex {
  Vec3 positon;
  Vec3 normalize;
  Vec3 color = Vec3(1.0f, 1.0f, 1.0f); // Màu sắc của đỉnh

  Vertex(Vec3 p, Vec3 n) : positon(p), normalize(n) {}
};
#endif
