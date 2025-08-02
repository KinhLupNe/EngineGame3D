#ifndef CULLING_H
#define CULLING_H
#include "../Geometry/Vertex.h"
#include "../Math/Math.h"
#include <vector>

// tính bitmark của vector
int computeClipCode(const Vec4 &a);

// is culling ?
bool linePrimitiveCulling(Vec4 a, Vec4 b);

// clip line with one plane
bool clipLineOnePlane(Vec4 &a, Vec4 &b, int plane);

// clip line with all 6 planes
bool ClipLine(Vec4 &a, Vec4 &b);

// point in or out the frustum ?
bool isInFrustum(const Vec4 &a, int plane);

// polygon after clipping
std::vector<Vec4> clipPolyWithPlane(const std::vector<Vec4> &inPoly, int plane);

//  new triangles after clipping old triangle
std::vector<TriangleOutput> clipTriangle(const TriangleOutput &triOut);
#endif
