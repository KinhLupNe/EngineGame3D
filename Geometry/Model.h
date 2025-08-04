#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
class Model {
public:
    Mesh *mesh;
    Vec3 position;
    Vec3 rotation{0,0,0};
    Vec3 scale{1, 1, 1};

    Model();
    ~Model();

    Model(Mesh *m);
    Model(const Vec3& pos);
    Model(const Vec3& pos, Mesh *m);
    Mat4 getWorldMatrix();
};
#endif