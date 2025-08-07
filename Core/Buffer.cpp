#include "Buffer.h"
#include <cstdint>
#include <vector>

void IndexBuffer::setData(const std::vector<uint32_t> &d) { data = d; }
uint32_t IndexBuffer::operator[](const uint32_t a) const { return data[a]; }
size_t IndexBuffer::getSize() const { return data.size(); }

std::vector<uint32_t> IndexBuffer::getData() const {
  return data;
}

void VertexBuffer::setData(const std::vector<Vertex> &d) { data = d; }
Vertex VertexBuffer::operator[](const uint32_t a) const { return data[a]; }
size_t VertexBuffer::getSize() const { return data.size(); }

std::vector<Vertex> VertexBuffer::getData() const {
  return data;
}

void Buffer::loadFromMesh(const Mesh &mesh) {
  ibo.setData(mesh.indices);
  vbo.setData(mesh.vertices);
}

IndexBuffer Buffer::getIBO() { return ibo; }
VertexBuffer Buffer::getVBO() { return vbo; }

void Buffer::setIbo(const IndexBuffer &ibo) {
  this->ibo = ibo;
}

void Buffer::setVbo(const VertexBuffer &vbo) {
  this->vbo = vbo;
}
