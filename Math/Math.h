#ifndef MATH_H
#define MATH_H

#include <cmath>
class Vec2 {
public:
  float x;
  float y;

  Vec2() = default;
  ~Vec2() = default;
  Vec2(float x, float y);
};
class Vec3 {
public:
  float x;

  float y;
  float z;

  Vec3();
  Vec3(float x, float y, float z);
  ~Vec3();

  Vec3 operator*(const Vec3 &other) const;
  Vec3 operator+(const Vec3 &other) const;
  Vec3 operator-(const Vec3 &other) const;

  void rotationVec3(float radX, float radY, float radZ);
  Vec3 normalize();
  static float crossPro(const Vec3 &a, const Vec3 &b, const Vec3 &c);
};

class Vec4 {
public:
  float x;
  float y;
  float z;
  float w;

  Vec4();
  Vec4(float x, float y, float z, float w);
  Vec4 operator+(const Vec4 &other) const;
  Vec4 operator-(const Vec4 &other) const;
  Vec4 operator*(const float &t) const;
  ~Vec4();
};

class Mat4 {
public:
  float m[4][4];

  Mat4();
  Mat4(float m[4][4]);
  ~Mat4();

  Mat4 operator*(const Mat4 &other) const;
  Vec4 operator*(const Vec4 &vec) const;

  static Mat4 getPositionMatrix(const Vec3 &p);
  static Mat4 getRotationMatrix(const Vec3 &r);
  static Mat4 getScaleMatrix(const Vec3 &s);
  static Mat4 lookAt(const Vec3 &pos, const Vec3 &target, const Vec3 &up);
  static Mat4 persentive(const float &zNear, const float &zFar, const float &r,
                         const float &l, const float &t, const float &b);
  static Mat4 viewport(const float &x, const float &y, const float &w,
                       const float &h, const float &n, const float &f);
};
// tam giác trong không gian 4d
struct Triangle {
  Vec4 v0;
  Vec4 v1;
  Vec4 v2;
};

#endif
