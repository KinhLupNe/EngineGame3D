#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H
#include "Light.h"
class AmbientLight : public Light {
public:
  Vec3 k; // hê số ambient, thường là 0.1f
  AmbientLight(const float &intensity = 1.0f,
               const Vec3 &color = Vec3(1.0f, 1.0f, 1.0f),
               const Vec3 &k = Vec3(0.1f, 0.1f, 0.1f))
      : Light{intensity, color} {}

  ~AmbientLight() override = default;

  // ánh sáng môi trường chiếu mọi hướng, méo dùng tới
  Vec3 getDirection(const Vec3 &point) const override { return Vec3(0, 0, 0); }
  // thông lượng ánh sáng tại điểm cần chiếu sáng là hằng số, khoảng 0.1 là ổn;
  Vec3 getRadiance(const Vec3 &point) const override { return k * intensity; }
  //  ánh sáng môi trường, méo dùng tới thằng này
  float getDistance(const Vec3 &point) const override { return 0.0f; }
};
#endif
