#include "Camera.h"

Camera::Camera(const Vec3 &pos, const Vec3 &target, const Vec3 &up,
               const float &zNear, const float &zFar, const float &r,
               const float &l, const float &t, const float &b)

    : pos(pos), target(target), up(up), zNear(zNear), zFar(zFar), r(r), l(l),
      t(t), b(b) {
  camAngle = Vec3(0, 0, 0); // Khởi tạo góc nhìn camera
}

Mat4 Camera::getViewMatrix() {
  Vec4 f = Vec4(-pos.x + target.x, -pos.y + target.y, -pos.z + target.z, 0.0f);
  f = Mat4::getRotationMatrix(Vec3(0.0f, 0.0f, 0.0f) - camAngle) * f;
  Vec3 fVec = Vec3(f.x, f.y, f.z).normalize();
  Vec3 center = fVec + pos; // Tính tâm của camera

  return Mat4::lookAt(pos, center, up);
}
Mat4 Camera::getProjectionMatrix() {
  return Mat4::persentive(zNear, zFar, r, l, t, b);
}
