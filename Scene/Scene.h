#ifndef SCENE_H
#define SCENE_H
#include "../Core/Camera.h"
#include "../Geometry/Model.h"
#include "../Math/Math.h"
class Scene {
public:
  Camera *camera = nullptr;
  std::vector<Model *> models;

  Scene() = default;
  ~Scene() = default;
  void addModel(Model *m);
  void removeModel(Model *m);
  void clearModels();
};

#endif
