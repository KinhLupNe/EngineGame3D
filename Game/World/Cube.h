#ifndef CUBE_H
#define CUBE_H
#include "../../Geometry/Model.h"
class Cube : public Model {
public:
  Cube() = default;
  Mesh m;
  Cube(const Vec3 &pos, const Vec3 &scale, const Vec3 &rotation,
       const Mesh &mesh)
      : m(mesh), Model(pos, &m) {
    this->scale = scale;
    this->rotation = rotation;
  }

  ~Cube() = default;
};
#endif
