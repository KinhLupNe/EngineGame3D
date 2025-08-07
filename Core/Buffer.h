/**
 * @file Buffer.h
 * @brief khai báo ibo bufer, vbo bufffer, xử lí ibo vbo
 */
#ifndef BUFFER_H
#define BUFFER_H

#include "../Geometry/Mesh.h"
#include "../Geometry/Vertex.h"
#include <cstddef>
#include <cstdint>
#include <vector>

class IndexBuffer {
private:
  std::vector<uint32_t> data;
  int ibo;

public:
  IndexBuffer() = default;

  ~IndexBuffer() = default;

  void setData(const std::vector<uint32_t> &d);

  uint32_t operator[](uint32_t a) const;

  size_t getSize() const;

  std::vector<uint32_t> getData() const;
};

class VertexBuffer {
private:
  std::vector<Vertex> data;

public:
  VertexBuffer() = default;

  ~VertexBuffer() = default;

  void setData(const std::vector<Vertex> &d);

  Vertex operator[](uint32_t a) const;

  size_t getSize() const;

  std::vector<Vertex> getData() const;
};

class Buffer {
private:
  IndexBuffer ibo;
  VertexBuffer vbo;

public:
  void loadFromMesh(const Mesh &mesh);

  void setIbo(const IndexBuffer &ibo);

  void setVbo(const VertexBuffer &vbo);

  IndexBuffer getIBO();

  VertexBuffer getVBO();
};

#endif
