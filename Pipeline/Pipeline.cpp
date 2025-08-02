#include "Pipeline.h"
#include "Culling.h"
#include "Rasterization.h"
#include <iostream>
#include <vector>
VertexOutput Pipeline::vertexShader(const Vertex &vertex,
                                    const Mat4 &modelMatrix,
                                    const Mat4 &viewMatrix,
                                    const Mat4 &projectionMatrix) {
  VertexOutput res;
  res.normal = vertex.normalize;
  res.color = vertex.color;
  res.posView = Vec3(vertex.positon.x, vertex.positon.y, vertex.positon.z);
  // Chuyển đổi vị trí của đỉnh từ không gian mô hình sang không gian clip
  Vec4 transformedVertex =
      modelMatrix *
      Vec4(vertex.positon.x, vertex.positon.y, vertex.positon.z, 1.0f);
  transformedVertex = viewMatrix * transformedVertex;
  transformedVertex = projectionMatrix * transformedVertex;
  res.posClip = transformedVertex;
  return res;
}
std::vector<TriangleOutput>
Pipeline::assemble(const std::vector<VertexOutput> &clipVertexs,
                   const std::vector<uint32_t> &idx) {
  std::vector<TriangleOutput> tris;
  float l = idx.size();
  for (int i = 0; i < l; i++) {
    TriangleOutput ex;
    ex.v0 = clipVertexs[idx[i]];
    ex.v1 = clipVertexs[idx[++i]];
    // std::cout << idx[i] << ",";
    ex.v2 = clipVertexs[idx[++i]];
    // std::cout << idx[i] << ",";
    tris.push_back(ex);
  }
  return tris;
}
bool Pipeline::backFaceCull(const TriangleOutput &triOut) {
  Vec3 ndcVer[3];
  Triangle tri = Triangle{Vec4(triOut.v0.posClip.x, triOut.v0.posClip.y,
                               triOut.v0.posClip.z, triOut.v0.posClip.w),
                          Vec4(triOut.v1.posClip.x, triOut.v1.posClip.y,
                               triOut.v1.posClip.z, triOut.v1.posClip.w),
                          Vec4(triOut.v2.posClip.x, triOut.v2.posClip.y,
                               triOut.v2.posClip.z, triOut.v2.posClip.w)};
  ndcVer[0] =
      Vec3(tri.v0.x / tri.v0.w, tri.v0.y / tri.v0.w, tri.v0.z / tri.v0.w);

  ndcVer[1] =
      Vec3(tri.v1.x / tri.v1.w, tri.v1.y / tri.v1.w, tri.v1.z / tri.v1.w);
  ndcVer[2] =
      Vec3(tri.v2.x / tri.v2.w, tri.v2.y / tri.v2.w, tri.v2.z / tri.v2.w);
  return Vec3::crossPro(ndcVer[0], ndcVer[1], ndcVer[2]) >= 0.0f;
}
// triangle primitive clipping

std::vector<TriangleOutput>
Pipeline::primitiveClipping(const TriangleOutput &tri) {
  return clipTriangle(tri);
}
// Rasterization
std::vector<VertexOutput> Pipeline::rasterization(const VertexOutput &a,
                                                  const VertexOutput &b,
                                                  const VertexOutput &c,
                                                  const Triangle &t) {
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
