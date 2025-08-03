#include "Camera.h"

Camera::Camera(Vec3 pos, float yaw, float pitch, float zNear, float zFar,
               float left, float right, float bottom, float top)
    : pos(pos), yaw(yaw), pitch(pitch), zNear(zNear), zFar(zFar), l(left),
      r(right), b(bottom), t(top) {}

Mat4 Camera::getViewMatrix() const {
  // 1) Tính forward sao cho yaw=0 → forward=(0,0,-1)
  Vec3 forward{std::cos(pitch) * std::sin(-yaw), std::sin(pitch),
               -std::cos(pitch) * std::cos(-yaw)};
  forward = forward.normalize();

  // 2) Tính right, up vector
  Vec3 worldUp{0.0f, 1.0f, 0.0f};
  Vec3 left = (forward * worldUp).normalize();
  Vec3 up = (left * forward).normalize();

  // 3) Build view matrix
  return Mat4::lookAt(pos, pos + forward, up);
}
Mat4 Camera::getProjectionMatrix() const {
  return Mat4::persentive(zNear, zFar, r, l, t, b);
}
Vec3 Camera::getForward() const {
  Vec3 forward{
      std::cos(pitch) * std::sin(yaw), std::sin(pitch),
      -std::cos(pitch) * std::cos(yaw) // dấu + ở đây
  };
  forward = forward.normalize();
  return forward;
}
