#include "FragmentShader.h"


FragmentPayLoad::FragmentPayLoad(const Vec3 &normal,
                                 const float &depth,
                                 const Vec3 &position,
                                 const Vec3 &color)
  : normal(normal), depth(depth), posW(position), color(color) {
}


// FragmentShader() = default;
FragmentShader::FragmentShader(const AmbientLight &ambientLight,
                               const DistantLight &distantLight,
                               const std::string &ramp)
  : ambientLight(ambientLight), distantLight(distantLight), ramp(ramp) {
}


char FragmentShader::shade() const {
  Vec3 L = distantLight.getDirection(Vec3(0, 0, 0));
  Vec3 N = fragmentPayLoad.normal;
  N = N.normalize(); // chuẩn hóa vector pháp tuyến
  // diffuse lighting
  float lambertian = Vec3::multi(L, N);
  Vec3 radianceD = distantLight.getRadiance(fragmentPayLoad.posW);
  Vec3 diffuse = radianceD * lambertian; // cường độ sáng diffuse
  //ambient lighttinh
  Vec3 ambient = ambientLight.getRadiance(fragmentPayLoad.posW); // cường độ sáng ambient

  // final lighting
  Vec3 finalColor = diffuse + ambient; // cường dộ sáng tổng hợp

  float I = (finalColor.x + finalColor.y + finalColor.z) / 3.0f;
  if (I < 0.0f) {
    I = 0.0f; // đảm bảo không có giá trị âm
  } else if (I > 1.0f) {
    I = 1.0f; // đảm bảo không có giá trị vượt quá 1
  }
  const float step = 1.0f / static_cast<float>(ramp.size());
  return ramp[static_cast<int>(I / step)];
}


