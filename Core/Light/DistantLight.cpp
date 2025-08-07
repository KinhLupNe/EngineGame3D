
#include "DistantLight.h"
#include <limits>

DistantLight::DistantLight(const Mat4 &l2w, const float &intensity = 1.0f,
                           const Vec3 &color = Vec3(1.0f, 1.0f, 1.0f))
    : Light{intensity, color} {
    Vec4 d = Vec4(dir.x, dir.y, dir.z, 0.0f);
    d = l2w * d;
    dir = Vec3(d.x, d.y, d.z);
    dir = dir.normalize();
}

Vec3 DistantLight::getDirection(const Vec3 & /*point*/) const { return dir; }

Vec3 DistantLight::getRadiance(const Vec3 & /*point*/) const {
    return color * intensity;
}

float DistantLight::getDistance(const Vec3 & /*point*/) const {
    return std::numeric_limits<float>::infinity();
}
