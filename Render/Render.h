#ifndef RENDER_H
#define RENDER_H
#include "../Core/Buffer.h"
#include "../Core/Camera.h"
#include "../Math/Math.h"
#include "../Pipeline/Pipeline.h"
#include "../Scene/Scene.h"
#include <vector>
using namespace std;
// inout :scene
class Render {
public:
  Pipeline p;
  vector<Buffer> bufffer;
  vector<IndexBuffer> ibos;
  vector<VertexBuffer> vbos;
  Scene scene;

  Render();
  ~Render();

  // display bufffer//
  //  clip vertexs
  vector<Vec4> clipVertex(const VertexBuffer &vbo, Model *model) {
    vector<Vec4> res;
    for (int i = 0; i < vbo.getSize(); i++) {
      Vec4 a = Vec4(vbo[i].positon.x, vbo[i].positon.y, vbo[i].positon.z, 1);
      Vec4 b = p.vertexShader(a, model->getWorldMatrix(),
                              scene.camera->getViewMatrix(),
                              scene.camera->getProjectionMatrix());
      res.push_back(b);
      return res;
    }
  }
  //
  void present();
};
#endif
