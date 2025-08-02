#ifndef CAMERA_H
#define CAMERA_H
#include "../Math/Math.h"
class Camera {
public:
  Vec3 pos;
  Vec3 target;
  Vec3 up;
  Vec3 camAngle; // góc nhìn của camera
  float zNear;
  float zFar;
  float r, l, t, b;

  Camera(const Vec3 &pos, const Vec3 &target, const Vec3 &up,
         const float &zNear, const float &zFar, const float &r, const float &l,
         const float &t, const float &b);

  ~Camera() = default;
  Mat4 getViewMatrix();
  Mat4 getProjectionMatrix();
};

#endif
