#ifndef PIPELINE_H
#define PIPELINE_H
#include "../Math/Math.h"
#include "Culling.h"
#include <cstdint>
#include <vector>

struct Pipeline {
  // Vertex shader : Lay ma toa trong trong khong gian phoi canh
  static Vec4 vertexShader(const Vec4 &vertex, const Mat4 &modelMatrix,
                           const Mat4 &viewMatrix,
                           const Mat4 &projectionMatrix);
  // ghep thanh cac tam giac
  static std::vector<Triangle> assemble(const std::vector<Vec4> &clipVertexs,
                                        const std::vector<uint32_t> &idx);

  // culling backspace;
  static bool backFaceCull(const Triangle &tri);

  // triangle primitive clipping
  // nằm ngoài trả về rỗng
  static std::vector<Triangle> primitiveClipping(const Triangle &tri);
  // Rasterization
  std::vector<Vec3> rasterization(const Vec3 &a, const Vec3 &b, const Vec3 &c);
  //  clip ->ndc->viewport
  static Vec3 toScreen(const int &width, const int &height,
                       const Vec4 &clipVertex);
};

#endif
