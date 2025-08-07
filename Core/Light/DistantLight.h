/**
 * @file DistantLight.h
 * @brief khởi tạo, xử lý ánh sáng thẳng ,xa, mặt trời, didffuse
 * @brief overide từ Light.h
 */
#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H
#include "Light.h"

class DistantLight : public Light {
private:
  // hướng ánh sáng trong không gian world( từ điểm đi cho dễ tính toán)
  Vec3 dir = Vec3(0.5f, 0.5f, 1.0f);

public:
  DistantLight() = default;

  ~DistantLight() override = default;

  DistantLight(const Mat4 &l2w, const float &intensity, const Vec3 &color);

  // hướng ánh sáng từ diem chieu sang den nguon sang, do song song nên chính là dir,
  Vec3 getDirection(const Vec3 & /*point*/) const override;

  // thông lượng ánh sáng tại điểm cần chiếu sáng
  Vec3 getRadiance(const Vec3 & /*point*/) const override;

  // trả về khoảng cách từ nguồn sáng đến điểm cần chiếu sáng, ở đây là xa vô hạn, méo dùng tới thằng này
  float getDistance(const Vec3 & /*point*/) const override;

  //-------setter, getter-------------------
  Vec3 getDir() const {
    return dir;
  }

  void setDir(const Vec3 &dir) {
    this->dir = dir;
  }
};
#endif
