#include "Culling.h"
#include <iostream>
#include <vector>
// tính bitmark của vector
int computeClipCode(const Vec4 &a) {
  int code = 0;
  if (a.x < -a.w)
    code = code | 1 << 0;
  if (a.x > a.w)
    code = code | 1 << 1;
  if (a.y < -a.w)
    code = code | 1 << 2;
  if (a.y > a.w)
    code = code | 1 << 3;
  if (a.z < -a.w)
    code = code | 1 << 4;
  if (a.z > a.w)
    code = code | 1 << 5;

  return code;
}

// is culling ?
bool linePrimitiveCulling(Vec4 a, Vec4 b) {
  int codeA = computeClipCode(a);
  int codeB = computeClipCode(b);

  if ((codeA & codeB) != 0) {
    return true; // bị culling
  }
  return false; // không bị culling̣̣(nằm trong hoặc bị cắt)
}
// 2 điểm nằm ở phía ngoài thì trả về false;
// 2 điểm nằm ở phía trong hoặc cắt thì trả về true, đồng thơi cập nhât tọa độ
// mới
//
bool clipLineOnePlane(Vec4 &a, Vec4 &b, int plane) {
  float fa, fb;
  switch (plane) {
  case 1:
    fa = a.x + a.w;
    fb = b.x + b.w;
    break;
  case 2:
    fa = a.x - a.w;
    fb = b.x - b.w;
    break;
  case 3:
    fa = a.y + a.w;
    fb = b.y + b.w;
    break;
  case 4:
    fa = a.y - a.w;
    fb = b.y - b.w;
    break;
  case 5:
    fa = a.z + a.w;
    fb = b.z + b.w;
    break;
  case 6:
    fa = a.z - a.w;
    fb = b.z - b.w;
    break;
  }
  bool isNegPlane = (plane % 2 == 1);
  if (isNegPlane) {

    if (fa >= 0 && fb >= 0)
      return true; // ca 2 o trong
    if (fa < 0 && fb < 0)
      return false; // ca 2 o ngoai
  } else {

    if (fa <= 0 && fb <= 0)
      return true; // ca 2 o trong
    if (fa > 0 && fb > 0)
      return false; // ca 2 o ngoai
  }
  float t = fa / (fa - fb);
  // cat: tim diem moi, cap nhat
  Vec4 P = Vec4(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y),
                a.z + t * (b.z - a.z), a.w + t * (b.w - a.w));
  if (isNegPlane) {

    if (fa < 0)
      a = P;
    else
      b = P;
  } else {

    if (fa > 0)
      a = P;
    else
      b = P;
  }
  return true; // hoan thien cat, 2 diem o trong
}
// trả về false nếu nó nằm ngoài
// trả về true vơi các trường hợp còn lại;

// clip line with all 6 planes
bool ClipLine(Vec4 &a, Vec4 &b) {
  for (int i = 1; i <= 6; i++) {
    if (!clipLineOnePlane(a, b, i)) {
      return false; // no nam ngoai roi cu oi
    }
  }
  return true; // hoan thanh viec cat
}

bool isInFrustum(const Vec4 &a, int plane) {
  switch (plane) {
  case 1:
    return (a.x >= -a.w);
  case 2:
    return (a.x <= a.w);
  case 3:
    return (a.y >= -a.w);
  case 4:
    return (a.y <= a.w);
  case 5:
    return (a.z >= -a.w);
  case 6:
    return (a.z <= a.w);
  }
  return false;
}

std::vector<Vec4> clipPolyWithPlane(const std::vector<Vec4> &inPoly,
                                    int plane) {
  std::vector<Vec4> outPoly;
  int n = inPoly.size();
  for (int i = 0; i < n; i++) {
    Vec4 a = inPoly[i % n];
    Vec4 b = inPoly[(i + 1) % n];

    bool ia = isInFrustum(a, plane);
    bool ib = isInFrustum(b, plane);
    // nếu cả 2 điểm đều nằm trong thì thêm b vào
    if (ia && ib) {
      outPoly.push_back(b);
    } else if (ia == true && ib == false) {
      // nếu a nằm trong và b nằm ngoài thì thêm giao điểm vào
      Vec4 newB = b;
      if (clipLineOnePlane(a, newB, plane)) {
        outPoly.push_back(newB);
      }
    } else if (ia == false && ib == true) {
      // nếu a nằm ngoài và b nằm trong thì thêm giao điểm vào
      // thêm b
      Vec4 newA = a;
      if (clipLineOnePlane(newA, b, plane)) {
        outPoly.push_back(newA);
      }
      outPoly.push_back(b);
    }
  }
  return outPoly;
}

std::vector<TriangleOutput> clipTriangle(const TriangleOutput &triOut) {
  Triangle tri = Triangle{Vec4(triOut.v0.posClip.x, triOut.v0.posClip.y,
                               triOut.v0.posClip.z, triOut.v0.posClip.w),
                          Vec4(triOut.v1.posClip.x, triOut.v1.posClip.y,
                               triOut.v1.posClip.z, triOut.v1.posClip.w),
                          Vec4(triOut.v2.posClip.x, triOut.v2.posClip.y,
                               triOut.v2.posClip.z, triOut.v2.posClip.w)};
  std::vector<Vec4> poly = {tri.v0, tri.v1, tri.v2};
  std::vector<TriangleOutput> res;
  TriangleOutput temp = triOut;
  // clip poly with 6 planes
  for (int i = 1; i <= 6; i++) {
    poly = clipPolyWithPlane(poly, i);
    // std::cout << "so dinh cua buoc poly thu " << i << ": " << poly.size()<<
    // std::endl;

    if (poly.size() < 3)
      return {};
    // std::cout << "size poly:" << poly.size();
  }
  // std::cout << "size poly:" << poly.size();

  // convert polygon to triangles

  Triangle t;
  int l = poly.size() - 2;
  for (int i = 0; i < l; i++) {
    t.v0 = poly[0];
    t.v1 = poly[i + 1];
    t.v2 = poly[i + 2];

    temp.v0.posClip = t.v0;
    temp.v1.posClip = t.v1;
    temp.v2.posClip = t.v2;

    res.push_back(temp);
  }
  // std::cout << "size poly : " << tris.size() << std::endl;
  return res;
}
