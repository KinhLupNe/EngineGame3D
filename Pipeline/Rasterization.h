#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include "../Math/Math.h"
#include <vector>
// cạnh , điểm trong
float crossProduct(const Vec2 &a, const Vec2 &b);
// 1 diem b co nam trong tam giac a khong ?
bool isOnTriangle(const float &a, const float &b, const float &c);
// tap cac diem trong tam giac
std::vector<Vec3> pointInTriagle(const Vec3 &a, const Vec3 &b, const Vec3 &c,
                                 const Triangle &t);
// noi suy dung phoi canh z-buffer
float zBuffer(const Vec3 &a, const Vec3 &b, const Vec3 &c, const float &w0,
              const float &w1, const float &w2, const Triangle &t);

#endif
