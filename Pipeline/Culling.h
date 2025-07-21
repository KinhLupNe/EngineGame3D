#ifndef CULLING_H
#define CULLING_H
#include "../Math/Math.h"

// tính bitmark của vector
int computeClipCode(float x, float y, float z, float w);

// is culling ?
bool linePrimitiveCulling(Vec4 a, Vec4 b);

bool clipLineOnePlane(Vec4 &a, Vec4 &b, int plane);
bool ClipLine(Vec4 &a, Vec4 &b);
#endif
