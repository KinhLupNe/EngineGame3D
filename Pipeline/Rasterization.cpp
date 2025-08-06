#include "Rasterization.h"
#include <cmath>
#include <iostream>
#include <vector>
float crossProduct(const Vec3 &a, const Vec3 &b) {
  return a.x * b.y - a.y * b.x;
}
bool isOnTriangle(const float &a, const float &b, const float &c) {
  if (a > 0 && b > 0 && c > 0)
    return true;
  return false;
}
// tap cac diem trong tam giac trong khong gian man hinh
std::vector<VertexOutput> pointInTriagle(const VertexOutput &aOut,
                                         const VertexOutput &bOut,
                                         const VertexOutput &cOut,
                                         const Triangle &t) {
  Vec3 a = aOut.posScreen;
  Vec3 b = bOut.posScreen;
  Vec3 c = cOut.posScreen;
  // std::cout << "a: " << a.x << ", " << a.y << ", " << a.z << std::endl;
  // std::cout << "b: " << b.x << ", " << b.y << ", " << b.z << std::endl;
  // std::cout << "c: " << c.x << ", " << c.y << ", " << c.z << std::endl;
  // std::cout << "a: " << aOut.posView.x << ", " << aOut.posView.y << ", "
  //        << aOut.posView.z << std::endl;
  // std::cout << "b: " << bOut.posView.x << ", " << bOut.posView.y << ", "
  //         << bOut.posView.z << std::endl;
  // std::cout << "c: " << cOut.posView.x << ", " << cOut.posView.y << ", "
  //         << cOut.posView.z << std::endl;

  std::vector<VertexOutput> res;
  Vec3 ab = b - a;
  Vec3 bc = c - b;
  Vec3 ca = a - c;

  // box boading
  float xMax = fmax(a.x, fmax(b.x, c.x));
  float xMin = fmin(a.x, fmin(b.x, c.x));
  float yMax = fmax(a.y, fmax(b.y, c.y));
  float yMin = fmin(a.y, fmin(b.y, c.y));
  // duyet box
  for (int i = (int)xMin; i <= xMax; i++) {
    for (int j = (int)yMin; j <= yMax; j++) {
      Vec3 p = Vec3(i, j, 0);
      Vec3 ap = p - a;
      Vec3 bp = p - b;
      Vec3 cp = p - c;
      // toa do trong tam
      float w2 = crossProduct(ab, ap);
      float w0 = crossProduct(bc, bp);
      float w1 = crossProduct(ca, cp);
      float area = crossProduct(ab, c - a);
      // kiem tra diem co nam trong tam giac khong
      if (isOnTriangle(w0, w1, w2)) {
        w0 /= area;
        w1 /= area;
        w2 /= area;
        // tinh z dung phoi canh
        p.z = zBuffer(a, b, c, w0, w1, w2, t);
        // nội suy posView,posClip, nội suy normal, nội suy color
        // gán giá trị cho VertexOutput
        VertexOutput pOut =
            interpolateVertexOutput(aOut, bOut, cOut, w0, w1, w2);
        pOut.posScreen = p;

        // thêm vào kết quả
        res.push_back(pOut);
      }
    }
  }

  return res;
}
// noi suy dung phoi canh z-buffer
float zBuffer(const Vec3 &a, const Vec3 &b, const Vec3 &c, const float &w0,
              const float &w1, const float &w2, const Triangle &t) {

  float res;
  // std::cout << "w1: " << w1 << ", w2: " << w2 << ", w0: " << w0 << std::endl;
  res = 1.0f / ((w0 / a.z) + (w1 / b.z) + (w2 / c.z));
  // std::cout << "z: " << resZ << std::endl;
  //  resW = w0 / t.v0.w + w1 / t.v1.w + w2 / t.v2.w;
  //  std::cout << "w: " << resW << std::endl;
  //  res = resZ / resW;
  //  std::cout << "res: " << res << std::endl;
  return res;
}
// nội suy posView, posClip, normal, color
VertexOutput interpolateVertexOutput(const VertexOutput &a,
                                     const VertexOutput &b,
                                     const VertexOutput &c, const float &w0,
                                     const float &w1, const float &w2) {
  VertexOutput res;
  res.posWorld = a.posWorld * w0 + b.posWorld * w1 + c.posWorld * w2;
  res.posView = a.posView * w0 + b.posView * w1 + c.posView * w2;
  res.posClip = a.posClip * w0 + b.posClip * w1 + c.posClip * w2;
  res.normal =
      ((b.posWorld - a.posWorld) * (c.posWorld - b.posWorld)).normalize();

  res.color = a.color * w0 + b.color * w1 + c.color * w2;
  return res;
}
