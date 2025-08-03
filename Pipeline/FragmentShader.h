#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include "../Core/Light/AmbientLight.h"
#include "../Core/Light/DistantLight.h"
#include "../Core/Light/Light.h"
#include "../Math/Math.h"
#include <algorithm>
#include <iostream>
#include <string>
struct FragmentPayLoad {
  Vec3 color;   // màu sắc của điểm ảnh
  Vec3 normal;  // vector pháp tuyến tại điểm ảnh
  float depth;  // độ sâu của điểm ảnh
  Vec3 posView; // vị trí của điểm ảnh trong không gian thế giới
  FragmentPayLoad(const Vec3 &normal = Vec3(0.0f, 0.0f, 1.0f),
                  const float &depth = 1.0f,
                  const Vec3 &position = Vec3(0.0f, 0.0f, 0.0f),
                  const Vec3 &color = Vec3(1.0f, 1.0f, 1.0f))
      : normal(normal), depth(depth), posView(position), color(color) {}
};

class FragmentShader {
public:
  FragmentPayLoad fragmentPayLoad; // thông tin về điểm ảnh
  AmbientLight ambientLight;
  DistantLight distantLight;
  std::string ramp;
  FragmentShader(const AmbientLight &ambientLight = AmbientLight(),
                 const DistantLight &distantLight =
                     DistantLight(Mat4::getRotationMatrix(Vec3(0, 0, 0)), 1.0f,
                                  Vec3(1.0f, 1.0f, 1.0f)),
                 const std::string &ramp = ".,:;*nM#@")
      : ambientLight(ambientLight), distantLight(distantLight), ramp(ramp) {}
  ~FragmentShader() = default;

  char shade() const {
    Vec3 L = distantLight.getDirection(Vec3(0, 0, 0));
    Vec3 N = fragmentPayLoad.normal;
    N = N.normalize(); // chuẩn hóa vector pháp tuyến
    // std::cout << "N: " << N.x << " " << N.y << " " << N.z << std::endl;
    //  std::cout << "L: " << L.x << " " << L.y << " " << L.z << std::endl;
    //    lamber cosine law
    float lambertian = Vec3::multi(L, N);
    // std::cout << "lambertian: " << lambertian << std::endl;
    Vec3 radianceD = distantLight.getRadiance(fragmentPayLoad.posView);
    Vec3 diffuse = radianceD * lambertian;

    Vec3 ambient = ambientLight.getRadiance(fragmentPayLoad.posView);
    Vec3 finalColor = diffuse + ambient;
    // std::cout << ambient.x << " " << ambient.y << " " << ambient.z <<
    // std::endl;
    //  std::cout << diffuse.x << " " << diffuse.y << " " << diffuse.z <<
    //  std::endl;
    //  std::cout << fragmentPayLoad.posView.x << " " <<
    //  fragmentPayLoad.posView.y
    //  << " " << fragmentPayLoad.posView.z << std::endl;
    //  std::cout << "finalColor: " << finalColor.x << " " << finalColor.y << "
    //  "
    //<< finalColor.z << std::endl;
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
