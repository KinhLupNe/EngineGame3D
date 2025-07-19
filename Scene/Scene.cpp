#include "Scene.h"
#include <cstddef>

void Scene::addModel(Model *m) {
  if (m != nullptr)
    models.push_back(m);
}
void Scene::removeModel(Model *m) {
  auto it = find(models.begin(), models.end(), m);
  if (it != models.end())
    models.erase(it);
}
void Scene::clearModels() { models.clear(); }
