#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include "../Core/Light/AmbientLight.h"
#include "../Core/Light/DistantLight.h"
#include "../Core/Light/Light.h"
#include "../Debugger/DebugLogger.h"
#include "../Math/Math.h"
#include <algorithm>
#include <iostream>
#include <string>
struct FragmentPayLoad {
  Vec3 color;  // màu sắc của điểm ảnh
  Vec3 normal; // vector pháp tuyến tại điểm ảnh
  float depth; // độ sâu của điểm ảnh
  Vec3 posW;   // vị trí của điểm ảnh trong không gian thế giới
  ~FragmentPayLoad() = default;
  FragmentPayLoad(const Vec3 &normal = Vec3(0.0f, 0.0f, 1.0f),
                  const float &depth = 1.0f,
                  const Vec3 &position = Vec3(0.0f, 0.0f, 0.0f),
                  const Vec3 &color = Vec3(1.0f, 1.0f, 1.0f))
      : normal(normal), depth(depth), posW(position), color(color) {}
};

class FragmentShader {
public:
  FragmentPayLoad fragmentPayLoad; // thông tin về điểm ảnh
  AmbientLight ambientLight;
  DistantLight distantLight;
  std::string ramp;
  // FragmentShader() = default;
  FragmentShader(const AmbientLight &ambientLight = AmbientLight(),
                 const DistantLight &distantLight =
                     DistantLight(Mat4::getRotationMatrix(Vec3(0, 0, 0)), 1.0f,
                                  Vec3(1.0f, 1.0f, 1.0f)),
                 const std::string &ramp = ".,:;+*onm@")
      : ambientLight(ambientLight), distantLight(distantLight), ramp(ramp) {}
  ~FragmentShader() = default;

  char shade() const {
    Vec3 L = distantLight.getDirection(Vec3(0, 0, 0));
    Vec3 N = fragmentPayLoad.normal;
    N = N.normalize(); // chuẩn hóa vector pháp tuyến
    float lambertian = Vec3::multi(L, N);
    Vec3 radianceD = distantLight.getRadiance(fragmentPayLoad.posW);
    Vec3 diffuse = radianceD * lambertian;
    auto &log = DebugLogger::Instance();

    Vec3 ambient = ambientLight.getRadiance(fragmentPayLoad.posW);
    Vec3 finalColor = diffuse + ambient;

    float I = (finalColor.x + finalColor.y + finalColor.z) / 3.0f;
    // std::cout << "I: " << I << std::endl;
    if (I < 0.0f) {
      I = 0.0f; // đảm bảo không có giá trị âm
    } else if (I > 1.0f) {
      I = 1.0f; // đảm bảo không có giá trị vượt quá 1
    }
    float step = 1.0f / (float)(ramp.size());
    return ramp[(int)(I / step)];
    // return I;
  }
};
#endif
