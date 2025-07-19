#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
class Model {
public:
  Mesh *mesh;
  Vec3 position;
  Vec3 rotation;
  Vec3 scale{1, 1, 1};

  Model();
  ~Model();

  Model(Mesh *m);
  Mat4 getWorldMatrix();
};
#endif
