#include "Pipeline.h"
#include <vector>

Vec4 Pipeline::vertexShader(const Vec4 &vertex, const Mat4 &modelMatrix,
                            const Mat4 &viewMatrix,
                            const Mat4 &projectionMatrix) {
  Vec4 transformedVertex = modelMatrix * vertex;
  transformedVertex = viewMatrix * transformedVertex;
  transformedVertex = projectionMatrix * transformedVertex;
  return transformedVertex;
}
std::vector<Triangle> Pipeline::assemble(const std::vector<Vec4> &clipVertexs,
                                         const std::vector<uint32_t> &idx) {
  std::vector<Triangle> tris;
  float l = idx.size();
  for (int i = 0; i < l; i += 3) {
    Triangle ex;
    ex.v0 = clipVertexs[idx[i]];
    ex.v1 = clipVertexs[idx[i + 1]];
    ex.v2 = clipVertexs[idx[i + 2]];
    tris.push_back(ex);
  }
  return tris;
}

Vec3 Pipeline::toScreen(const int &width, const int &height,
                        const Vec4 &clipVertex) {
  Mat4 a = Mat4::viewport(0, 0, width, height, 0, 1);
  // clip-> ndcVertex
  Vec4 ndcVertex =
      Vec4(clipVertex.x / clipVertex.w, clipVertex.y / clipVertex.w,
           clipVertex.z / clipVertex.w, 1);
  // ndc->viewport
  Vec4 temp = a * ndcVertex;
  Vec3 res = Vec3(temp.x, temp.y, temp.z);
  return res;
}
