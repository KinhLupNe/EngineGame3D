#ifndef PIPELINE_H
#define PIPELINE_H
#include "../Math/Math.h"
#include <cstdint>
#include <vector>

struct Triangle {
    Vec4 v0, v1, v2;
};
struct Pipeline {
  // Vertex shader : Lay ma toa trong trong khong gian phoi canh
  static Vec4 vertexShader(const Vec4 &vertex, const Mat4 &modelMatrix,
                    const Mat4 &viewMatrix, const Mat4 &projectionMatrix);
  // ghep thanh cac tam giac


  static std::vector<Triangle> assemble(const std::vector<Vec4> &clipVertexs,
                                 const std::vector<uint32_t> &idx);
  // clip ->ndc->viewport
  static Vec3 toScreen(const int &width, const int &height, const Vec4 &clipVertex);
};


#endif
