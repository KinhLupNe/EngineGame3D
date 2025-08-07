#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include "../Geometry/Vertex.h"
#include "../Math/Math.h"
#include <vector>

// tính cross product
float crossProduct(const Vec2 &a, const Vec2 &b);

// 1 diem b co nam trong tam giac a khong ?
bool isOnTriangle(const float &a, const float &b, const float &c);

// tap cac diem trong tam giac
std::vector<VertexOutput> pointInTriagle(const VertexOutput &a,
                                         const VertexOutput &b,
                                         const VertexOutput &c,
                                         const Triangle &t);

// noi suy thuộc tính z điểm đúng phoi canh
float zBuffer(const Vec3 &a, const Vec3 &b, const Vec3 &c, const float &w0,
              const float &w1, const float &w2, const Triangle &t);

// nội suy các thuộc tính (khác với z)
VertexOutput interpolateVertexOutput(const VertexOutput &aOut,
                                     const VertexOutput &bOut,
                                     const VertexOutput &cOut, const float &w0,
                                     const float &w1, const float &w2);
#endif
