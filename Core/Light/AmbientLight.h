#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H
#include "Light.h"

class AmbientLight : public Light {
private:
    Vec3 k; // hê số ambient, thường là 0.1f
public:
    AmbientLight() = default;

    ~AmbientLight() override = default;

    AmbientLight(const float &intensity,
                 const Vec3 &color,
                 const Vec3 &k);

    // ánh sáng môi trường chiếu mọi hướng, méo dùng tới
    Vec3 getDirection(const Vec3 &point) const override;

    // thông lượng ánh sáng tại điểm cần chiếu sáng là hằng số, khoảng 0.1 là ổn;
    Vec3 getRadiance(const Vec3 &point) const override;

    //  ánh sáng môi trường, méo dùng tới thằng này
    float getDistance(const Vec3 &point) const override;

    //----------getter, setter-------------------
    Vec3 &get_k() {
        return k;
    }

    void set_k(const Vec3 &k) {
        this->k = k;
    }
};
#endif
