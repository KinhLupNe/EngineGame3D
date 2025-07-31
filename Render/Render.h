#ifndef RENDER_H
#define RENDER_H
#include "../Core/Buffer.h"
#include "../Core/Camera.h"
#include "../Math/Math.h"
#include "../Pipeline/Pipeline.h"
#include "../Scene/Scene.h"
#include "FrameBuffer.h"
#include <vector>
using namespace std;
// inout :scene
class Render {
public:
  Pipeline p;
  vector<Buffer> buffers;
  vector<IndexBuffer> ibos;
  vector<VertexBuffer> vbos;
  Scene scene;
  int width;
  int height;
  FrameBuffer frameBuffer;

  Render(const int &width, const int &height)
      : width(width), height(height), frameBuffer(width, height) {}
  ~Render() = default;

  // display bufffer//
  // load buffer from model (vbo,ibo)
  void loadFromModel(const Model &model) {
    Buffer buffer;
    buffer.loadFromMesh(*model.mesh);
    ibos.push_back(buffer.getIBO());
    vbos.push_back(buffer.getVBO());
    buffers.push_back(buffer);
  }

  //  get Triangle in clip space (model ->view->project ->triangle)
  vector<Triangle> getTriangleClip(const VertexBuffer &vbo,
                                   const IndexBuffer &ibo, Model *model);
  // rassterization(tri(after backFaceCull, primitiveClipping) )
  vector<Vec3> VPbuffer(const Triangle &tri);

  void present();
};
#endif
