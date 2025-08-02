#ifndef PIPELINE_H
#define PIPELINE_H
#include "../Geometry/Vertex.h"
#include "../Math/Math.h"
#include "Culling.h"
#include <cstdint>
#include <vector>

struct Pipeline {
  // Vertex shader : Lay ma toa trong trong khong gian phoi canh
  static VertexOutput vertexShader(const Vertex &vertex,
                                   const Mat4 &modelMatrix,
                                   const Mat4 &viewMatrix,
                                   const Mat4 &projectionMatrix);
  // ghep thanh cac tam giac
  static std::vector<TriangleOutput>
  assemble(const std::vector<VertexOutput> &clipVertexs,
           const std::vector<uint32_t> &idx);

  // culling backspace;
  static bool backFaceCull(const TriangleOutput &triOut);

  // triangle primitive clipping
  // nằm ngoài trả về rỗng
  static std::vector<TriangleOutput>
  primitiveClipping(const TriangleOutput &tri);
  // Rasterization
  std::vector<VertexOutput> rasterization(const VertexOutput &a,
                                          const VertexOutput &b,
                                          const VertexOutput &c,
                                          const Triangle &t);
  //  clip ->ndc->viewport
  static Vec3 toScreen(const int &width, const int &height,
                       const Vec4 &clipVertex);
};

#endif
