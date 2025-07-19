#ifndef BUFFER_H
#define BUFFER_H

#include "../Geometry/Mesh.h"
#include "../Geometry/Vertex.h"
#include <cstddef>
#include <cstdint>
#include <vector>
class IndexBuffer {
public:
  std::vector<uint32_t> data;

  IndexBuffer() = default;
  ~IndexBuffer() = default;

  void setData(std::vector<uint32_t> d);
  uint32_t operator[](uint32_t a) const;
  size_t getSize() const;
};

class VertexBuffer {
public:
  std::vector<Vertex> data;

  VertexBuffer() = default;
  ~VertexBuffer() = default;

  void setData(std::vector<Vertex> d);
  Vertex operator[](uint32_t a) const;
  size_t getSize() const;
};

class Buffer {
public:
  IndexBuffer ibo;
  VertexBuffer vbo;

  void loadFromMesh(Mesh &mesh);

  IndexBuffer getIBO();
  VertexBuffer getVBO();
};

#endif
