#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H
#include "Light.h"
#include <limits>

class DistantLight : public Light {
public:
  Vec3 dir = Vec3(0.5f, 0.5f,
                  1.0f); // hướng chiếu sáng (mặc định là theo chiều âm trục Z)
  DistantLight(const Mat4 &l2w, const float &intensity = 1.0f,
               const Vec3 &color = Vec3(1.0f, 1.0f, 1.0f))
    : Light{intensity, color} {
    Vec4 d = Vec4(dir.x, dir.y, dir.z, 0.0f);
    d = l2w * d;
    dir = Vec3(d.x, d.y, d.z);
    dir = dir.normalize();
  }

  ~DistantLight() override = default;

  // hướng ánh sáng từ diem chieu sang den nguon sang, do song song nên
  // chính là dir,
  Vec3 getDirection(const Vec3 & /*point*/) const override { return dir; }

  // thông lượng ánh sáng tại điểm cần chiếu sáng
  Vec3 getRadiance(const Vec3 & /*point*/) const override {
    return color * intensity;
  }

  // trả về khoảng cách từ nguồn sáng đến điểm cần chiếu sáng, ở đây là xa vô
  // hạn, méo dùng tới thằng này
  float getDistance(const Vec3 & /*point*/) const override {
    return std::numeric_limits<float>::infinity();
  }
};
#endif
