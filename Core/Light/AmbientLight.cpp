
#include "AmbientLight.h"

AmbientLight::AmbientLight(const float &intensity = 1.0f,
                           const Vec3 &color = Vec3(1.0f, 1.0f, 1.0f),
                           const Vec3 &k = Vec3(0.1f, 0.1f, 0.1f))
    : Light{intensity, color}, k(k) {
}

// ánh sáng môi trường chiếu mọi hướng, méo dùng tới
Vec3 AmbientLight::getDirection(const Vec3 &point) const { return Vec3(0, 0, 0); }

// thông lượng ánh sáng tại điểm cần chiếu sáng là hằng số, khoảng 0.1 là ổn;
Vec3 AmbientLight::getRadiance(const Vec3 &point) const {
    return k * intensity;
}

//  ánh sáng môi trường, méo dùng tới thằng này
float AmbientLight::getDistance(const Vec3 &point) const { return 0.0f; }



