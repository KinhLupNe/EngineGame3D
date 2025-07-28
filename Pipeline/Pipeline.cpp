#include "Pipeline.h"
#include "Culling.h"
#include "Rasterization.h"
#include <iostream>
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
  for (int i = 0; i < l; i++) {
    Triangle ex;
    ex.v0 = clipVertexs[idx[i]];
    ex.v1 = clipVertexs[idx[++i]];
    // std::cout << idx[i] << ",";
    ex.v2 = clipVertexs[idx[++i]];
    // std::cout << idx[i] << ",";
    tris.push_back(ex);
  }
  return tris;
}
bool Pipeline::backFaceCull(const Triangle &tri) {
  Vec3 ndcVer[3];

  ndcVer[0] =
      Vec3(tri.v0.x / tri.v0.w, tri.v0.y / tri.v0.w, tri.v0.z / tri.v0.w);

  ndcVer[1] =
      Vec3(tri.v1.x / tri.v1.w, tri.v1.y / tri.v1.w, tri.v1.z / tri.v1.w);
  ndcVer[2] =
      Vec3(tri.v2.x / tri.v2.w, tri.v2.y / tri.v2.w, tri.v2.z / tri.v2.w);
  return Vec3::crossPro(ndcVer[0], ndcVer[1], ndcVer[2]) >= 0.0f;
}
// triangle primitive clipping

std::vector<Triangle> Pipeline::primitiveClipping(const Triangle &tri) {
  return clipTriangle(tri);
}
// Rasterization
std::vector<Vec3> Pipeline::rasterization(const Vec3 &a, const Vec3 &b,
                                          const Vec3 &c, const Triangle &t) {
  return pointInTriagle(a, b, c, t);
}
Vec3 Pipeline::toScreen(const int &width, const int &height,
                        const Vec4 &clipVertex) {
  Mat4 a = Mat4::viewport(2, 2, width, height, 0, 1);
  // clip-> ndcVertex
  Vec4 ndcVertex =
      Vec4(clipVertex.x / clipVertex.w, clipVertex.y / clipVertex.w,
           clipVertex.z / clipVertex.w, 1);
  // ndc->viewport
  Vec4 temp = a * ndcVertex;
  Vec3 res = Vec3(temp.x, temp.y, temp.z);
  return res;
}
