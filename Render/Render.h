/**
 * @file Render.h
 * @brief  khởi tạp mọi thông số của engine. pipeline đồ họa hoàn chỉnh
 */
#ifndef RENDER_H
#define RENDER_H
#include "../Core/Buffer.h"
#include "../Pipeline/Pipeline.h"
#include "../Scene/Scene.h"
#include "FrameBuffer.h"
#include <vector>
using namespace std;

// inout :scene
class Render {
private:
  vector<Buffer> buffers;
  vector<IndexBuffer> ibos;
  vector<VertexBuffer> vbos;
  Scene scene;
  int width;
  int height;
  FrameBuffer frameBuffer;

public:
  //singleton
  Pipeline p;

  Render() = default;

  Render(const int &width, const int &height)
    : width(width), height(height), frameBuffer(width, height) {
  }

  ~Render() = default;

  // load các model vào buffer(vbo, ibo)
  void loadFromModel(const Model &model) {
    Buffer buffer;
    buffer.loadFromMesh(*model.mesh);
    ibos.push_back(buffer.getIBO());
    vbos.push_back(buffer.getVBO());
    buffers.push_back(buffer);
  }

  //  get Triangle in clip space (model ->view->project ->triangle)
  // trả về tập các tam giác sau khi được chiến phối cảnh cách điểm
  vector<TriangleOutput> getTriangleClip(const VertexBuffer &vbo,
                                         const IndexBuffer &ibo, Model *model) const;

  // rassterization (tri(after backFaceCull, primitiveClipping) )
  vector<VertexOutput> VPbuffer(const TriangleOutput &triOut) const;

  // debug logger
  void cameraInfo() const;

  // render
  void present();

  // ---------setter, gettter----------------
  vector<Buffer> &getBuffers() {
    return buffers;
  }

  void setBuffer(const vector<Buffer> &buffers) {
    this->buffers = buffers;
  }

  vector<IndexBuffer> &betIbos() {
    return ibos;
  }

  void setIbos(const vector<IndexBuffer> &ibos) {
    this->ibos = ibos;
  }

  vector<VertexBuffer> &getVbos() {
    return vbos;
  }

  void setVbos(const vector<VertexBuffer> &vbos) {
    this->vbos = vbos;
  }

  Scene &getScene() {
    return scene;
  }

  void setScene(const Scene &scene) {
    this->scene = scene;
  }

  int &getWidth() {
    return width;
  }

  void setWidth(int width) {
    this->width = width;
  }

  int &getHeight() {
    return height;
  }

  void setHeight(int height) {
    this->height = height;
  }

  FrameBuffer &getFrameBuffer() {
    return frameBuffer;
  }

  void setFrameBuffer(const FrameBuffer &frame_buffer) {
    frameBuffer = frame_buffer;
  }
};
#endif
