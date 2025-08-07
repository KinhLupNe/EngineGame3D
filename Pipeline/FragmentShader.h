#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include "../Core/Light/AmbientLight.h"
#include "../Core/Light/DistantLight.h"

#include "../Math/Math.h"


#include <string>

struct FragmentPayLoad {
  Vec3 normal; // vector pháp tuyến tại điểm ảnh
  float depth; // độ sâu của điểm ảnh
  Vec3 posW; // vị trí của điểm ảnh trong không gian thế giới
  Vec3 color; // màu sắc của điểm ảnh

  FragmentPayLoad() = default;

  ~FragmentPayLoad() = default;

  FragmentPayLoad(const Vec3 &normal,
                  const float &depth,
                  const Vec3 &position,
                  const Vec3 &color);
};

class FragmentShader {
private:
  FragmentPayLoad fragmentPayLoad; // thông tin về điểm ảnh
  AmbientLight ambientLight;
  DistantLight distantLight;
  std::string ramp;

public:
  // FragmentShader() = default;
  FragmentShader(const AmbientLight &ambientLight = AmbientLight(),
                 const DistantLight &distantLight =
                     DistantLight(Mat4::getRotationMatrix(Vec3(0, 0, 0)), 1.0f,
                                  Vec3(1.0f, 1.0f, 1.0f)),
                 const std::string &ramp = ".,:;+*omM@");

  ~FragmentShader() = default;

  char shade() const;

  //------getter, setter-----------------------------
  FragmentPayLoad &getFragmentPayLoad() {
    return fragmentPayLoad;
  }

  void setFragmentPayLoad(const FragmentPayLoad &fragment_pay_load) {
    fragmentPayLoad = fragment_pay_load;
  }

  AmbientLight &getAmbientLight() {
    return ambientLight;
  }

  void setAmbientLight(const AmbientLight &ambient_light) {
    ambientLight = ambient_light;
  }

  DistantLight &getDistantLight() {
    return distantLight;
  }

  void setDistantLight(const DistantLight &distant_light) {
    distantLight = distant_light;
  }

  std::string &getRamp() {
    return ramp;
  }

  void setRamp(const std::string &ramp) {
    this->ramp = ramp;
  }
};
#endif
