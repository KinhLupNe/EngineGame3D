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
std::vector<Vec3> pointInTriagle(const Vec3 &a, const Vec3 &b, const Vec3 &c,
                                 const Triangle &t) {
  std::vector<Vec3> res;
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
      float w0 = crossProduct(ab, ap);
      float w1 = crossProduct(bc, bp);
      float w2 = crossProduct(ca, cp);
      float area = crossProduct(ab, c - a);
      // kiem tra diem co nam trong tam giac khong
      if (isOnTriangle(w0, w1, w2)) {
        w0 /= area;
        w1 /= area;
        w2 /= area;
        // tinh z dung phoi canh
        p.z = zBuffer(a, b, c, w0, w1, w2, t);
        res.push_back(p);
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
  res = ((w0 / t.v0.w) + (w1 / t.v1.w) + (w2 / t.v2.w)) /
        ((w0 / t.v0.z) + (w1 / t.v1.z) + (w2 / t.v2.z));
  // std::cout << "z: " << res << std::endl;
  return res;
}
