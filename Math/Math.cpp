#include "Math.h"
#include <cmath>
using namespace std;
Vec3::Vec3() {};
Vec3::~Vec3() {};

Vec4::Vec4() {};
Vec4::~Vec4() {};

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}
Vec3::Vec3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vec3 Vec3::operator*(const Vec3 &other) const {
  Vec3 res;
  res.x = y * other.z - z * other.y;
  res.y = z * other.x - x * other.z;
  res.z = x * other.y - y * other.x;
  return res;
}

Vec3 Vec3::operator+(const Vec3 &other) const {
  Vec3 res;
  res.x = x + other.x;
  res.y = y + other.y;
  res.z = z + other.z;
  return res;
}
Vec3 Vec3::operator-(const Vec3 &other) const {
  Vec3 res;
  res.x = x - other.x;
  res.y = y - other.y;
  res.z = z - other.z;
  return res;
}
Vec3 Vec3::operator*(const float &t) const {
  Vec3 res;
  res.x = x * t;
  res.y = y * t;
  res.z = z * t;
  return res;
}

float Vec3::multi(const Vec3 &a, const Vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vec3 Vec3::normalize() {
  float l = sqrt(x * x + y * y + z * z);
  Vec3 res = Vec3(x / l, y / l, z / l);
  return res;
}

float Vec3::crossPro(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
bool Vec3::operator==(const Vec3 &o) const {
  // Nếu muốn so sánh float an toàn hơn, có thể thay bằng khoảng epsilon
  return x == o.x && y == o.y && z == o.z;
}

 bool Vec3::operator!=(const Vec3 &o) const { return !(*this == o); }
Vec4::Vec4(float x, float y, float z, float w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}
Vec4 Vec4::operator+(const Vec4 &other) const {
  return Vec4(this->x + other.x, this->y + other.y, this->z + other.z,
              this->w + other.w);
}
Vec4 Vec4::operator-(const Vec4 &other) const {
  return Vec4(this->x - other.x, this->y - other.y, this->z - other.z,
              this->w - other.w);
}
Vec4 Vec4::operator*(const float &t) const {
  return Vec4(this->x * t, this->y * t, this->z * t, this->w * t);
}
void Vec3::rotationVec3(float radX, float radY, float radZ) {
  float cosy = cos(radX);
  float siny = sin(radX);
  float y1 = y * cosy - z * siny;
  float z1 = y * siny + z * cosy;

  y = y1;
  z = z1;

  float cosx = cos(radY);
  float sinx = sin(radY);
  float x1 = x * cosx + z * sinx;
  float z2 = -x * sinx + z * cosx;

  x = x1;
  z = z2;

  float cosz = cos(radZ);
  float sinz = sin(radZ);
  float x2 = x * cosz - y * sinz;
  float y2 = x * sinz + y * cosz;

  x = x2;
  y = y2;
}
Mat4::Mat4() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      this->m[i][j] = 0;
    }
  }
}

Mat4::~Mat4() = default;
Mat4::Mat4(float m[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      this->m[i][j] = m[i][j];
    }
  }
}

Mat4 Mat4::operator*(const Mat4 &other) const {
  Mat4 res;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        res.m[i][j] += this->m[i][k] * other.m[k][j];
      }
    }
  }
  return res;
}

Vec4 Mat4::operator*(const Vec4 &vec) const {
  Vec4 res;
  res.x = this->m[0][0] * vec.x + this->m[0][1] * vec.y +
          this->m[0][2] * vec.z + this->m[0][3] * vec.w;
  res.y = this->m[1][0] * vec.x + this->m[1][1] * vec.y +
          this->m[1][2] * vec.z + this->m[1][3] * vec.w;
  res.z = this->m[2][0] * vec.x + this->m[2][1] * vec.y +
          this->m[2][2] * vec.z + this->m[2][3] * vec.w;
  res.w = this->m[3][0] * vec.x + this->m[3][1] * vec.y +
          this->m[3][2] * vec.z + this->m[3][3] * vec.w;

  return res;
}

Mat4 Mat4::getPositionMatrix(const Vec3 &p) {
  float m[4][4] = {
      {1, 0, 0, p.x}, {0, 1, 0, p.y}, {0, 0, 1, p.z}, {0, 0, 0, 1}};
  Mat4 res = Mat4(m);
  return res;
}

Mat4 Mat4::getRotationMatrix(const Vec3 &r) {
  float mx[4][4] = {{1, 0, 0, 0},
                    {0, cos(r.x), -sin(r.x), 0},
                    {0, sin(r.x), cos(r.x), 0},
                    {0, 0, 0, 1}};
  Mat4 resX = Mat4(mx);

  float my[4][4] = {{cos(r.y), 0, sin(r.y), 0},
                    {0, 1, 0, 0},
                    {-sin(r.y), 0, cos(r.y), 0},
                    {0, 0, 0, 1}};
  Mat4 resY = Mat4(my);

  float mz[4][4] = {{cos(r.z), -sin(r.z), 0, 0},
                    {sin(r.z), cos(r.z), 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}};

  Mat4 resZ = Mat4(mz);
  return resZ * resY * resX;
}

Mat4 Mat4::getScaleMatrix(const Vec3 &s) {
  float m[4][4] = {
      {s.x, 0, 0, 0}, {0, s.y, 0, 0}, {0, 0, s.z, 0}, {0, 0, 0, 1}};

  Mat4 res = Mat4(m);
  return res;
}

Mat4 Mat4::lookAt(const Vec3 &pos, const Vec3 &target, const Vec3 &up) {
  Vec3 f = (target - pos).normalize();
  Vec3 s = (f * up).normalize();
  Vec3 u = up;

  float mb[4][4] = {{s.x, s.y, s.z, 0},
                    {u.x, u.y, u.z, 0},
                    {-f.x, -f.y, -f.z, 0},
                    {0, 0, 0, 1}};

  Mat4 M = Mat4(mb);

  float mp[4][4] = {
      {1, 0, 0, -pos.x}, {0, 1, 0, -pos.y}, {0, 0, 1, -pos.z}, {0, 0, 0, 1}};
  Mat4 R = Mat4(mp);

  return M * R;
}
Mat4 Mat4::persentive(const float &zNear, const float &zFar, const float &r,
                      const float &l, const float &t, const float &b) {
  float m[4][4] = {{(2 * zNear) / (r - l), 0, (r + l) / (r - l), 0},
                   {0, (2 * zNear) / (t - b), (t + b) / (t - b), 0},
                   {0, 0, -(zFar + zNear) / (zFar - zNear),(-2 * zFar * zNear) / (zFar - zNear) },
                   {0, 0, -1, 0}};
  Mat4 res = Mat4(m);
  return res;
}

Mat4 Mat4::viewport(const float &x, const float &y, const float &w,
                    const float &h, const float &n, const float &f) {
  float m[4][4] = {{w / 2, 0, 0, x + (w / 2)},
                   {0, h / 2, 0, y + (h / 2)},
                   {0, 0, (f - n) / 2, (f + n) / 2},
                   {0, 0, 0, 1}};
  Mat4 res = Mat4(m);
  return res;
}
