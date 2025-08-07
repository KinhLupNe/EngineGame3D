/**
 * @file scene.h
 * @brief khởi tạo scene
 */
#ifndef SCENE_H
#define SCENE_H
#include "../Core/Camera.h"
#include "../Geometry/Model.h"

class Scene {
private:
  Camera *camera = nullptr;
  std::vector<Model *> models;

public:
  Scene() = default;

  ~Scene() = default;

  void addModel(Model *m);

  void removeModel(Model *m);

  void clearModels();

  //-------------getter, setter-------------
  Camera *get_camera() const {
    return camera;
  }

  void set_camera(Camera *camera) {
    this->camera = camera;
  }

  std::vector<Model *> get_models() const {
    return models;
  }

  void set_models(const std::vector<Model *> &models) {
    this->models = models;
  }
};

#endif
