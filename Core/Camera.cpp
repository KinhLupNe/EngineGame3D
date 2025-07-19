#include "Camera.h"

Camera::Camera(const Vec3 &pos, const Vec3 &target, const Vec3 &up,
               const float &zNear, const float &zFar, const float &r,
               const float &l, const float &t, const float &b)

    : pos(pos), target(target), up(up), zNear(zNear), zFar(zFar), r(r), l(l),
      t(t), b(b) {}

Mat4 Camera::getViewMatrix() { return Mat4::lookAt(pos, target, up); }
Mat4 Camera::getProjectionMatrix() {
  return Mat4::persentive(zNear, zFar, r, l, t, b);
}
