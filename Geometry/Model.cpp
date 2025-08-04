#include "Model.h"
#include "Mesh.h"
Model::Model() = default;
Model::~Model() = default;
Model::Model(Mesh *m) : mesh(m) {};
Model::Model(const Vec3& pos): position(pos) {};
Model::Model(const Vec3& pos, Mesh *m): position(pos), mesh(m) {};

Mat4 Model::getWorldMatrix() {
  Mat4 res;
  Mat4 P = Mat4::getPositionMatrix(position);
  Mat4 R = Mat4::getRotationMatrix(rotation);
  Mat4 S = Mat4::getScaleMatrix(scale);
  res = P * R * S;
  return res;
}