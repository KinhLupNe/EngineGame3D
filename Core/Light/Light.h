#ifndef LIGHT_H
#define LIGHT_H
#include "../../Math/math.h"
class Light {
public:
  float intensity;
  Vec3 color;

  Light(const float &intensity = 1.0f,
        const Vec3 &color = Vec3(1.0f, 1.0f, 1.0f))
      : intensity(intensity), color(color) {}
  virtual ~Light() = default;
  // hướng ánh sáng từ nguồn sáng đến điểm cần chiếu sáng
  virtual Vec3 getDirection(const Vec3 &point) const = 0;

  // thông lượng ánh sáng tại điểm cần chiếu sáng
  virtual Vec3 getRadiance(const Vec3 &point) const = 0;

  // khoảng cách từ nguồn sáng đến điểm cần chiếu sáng
  virtual float getDistance(const Vec3 &point) const = 0;
};
#endif
