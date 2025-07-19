#include "Buffer.h"
#include <cstddef>
#include <cstdint>
#include <vector>

void IndexBuffer::setData(std::vector<uint32_t> d) { data = d; }
uint32_t IndexBuffer::operator[](uint32_t a) const { return data[a]; }
size_t IndexBuffer::getSize() const { return data.size(); }

void VertexBuffer::setData(std::vector<Vertex> d) { data = d; }
Vertex VertexBuffer::operator[](uint32_t a) const { return data[a]; }
size_t VertexBuffer::getSize() const { return data.size(); }

void Buffer::loadFromMesh(Mesh &mesh) {
  ibo.setData(mesh.indices);
  vbo.setData(mesh.vertices);
}

IndexBuffer Buffer::getIBO() { return ibo; }
VertexBuffer Buffer::getVBO() { return vbo; }
