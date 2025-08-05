#ifndef MESH_H
#define MESH_H
#include <algorithm>

#include "../Core/VoxelGrid.h"
#include "Vertex.h"
#include <unordered_map>
#include <vector>
class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;

  static Mesh createTriangle(Vec3 a, Vec3 b, Vec3 c);
  // static Mesh createRectangle();
  static Mesh createCube(float const &w, float const &h, float const &l);
  Mesh();
  ~Mesh();

  //---------------------------

  std::unordered_map<Vec3, uint32_t> vertexMap;

  // Lấy index của một vị trí, thêm mới nếu chưa có
  uint32_t getVertexIndex(const Vec3 &pos) {
    auto it = vertexMap.find(pos);
    if (it != vertexMap.end()) {
      return it->second;
    } else {
      uint32_t newIndex = static_cast<uint32_t>(vertices.size());
      vertices.push_back(Vertex{pos, Vec3(0, 0, 0)});
      vertexMap[pos] = newIndex;
      return newIndex;
    }
  }

  // Thêm một quad với 4 đỉnh không lặp
  void addQuad(const Vec3 &pos, const Vec3 &normal) {
    Vec3 du, dv;
    // Xác định hai cạnh vuông góc
    if (normal.x != 0) {
      du = Vec3{0, 1, 0};
      dv = Vec3{0, 0, 1};
    } else if (normal.y != 0) {
      du = Vec3{1, 0, 0};
      dv = Vec3{0, 0, 1};
    } else {
      du = Vec3{1, 0, 0};
      dv = Vec3{0, 1, 0};
    }

    // 4 đỉnh của quad
    Vec3 p0 = pos;
    Vec3 p1 = pos + du;
    Vec3 p2 = pos + du + dv;
    Vec3 p3 = pos + dv;

    // Lấy index (tự động thêm mới nếu cần)
    uint32_t i0 = getVertexIndex(p0);
    uint32_t i1 = getVertexIndex(p1);
    uint32_t i2 = getVertexIndex(p2);
    uint32_t i3 = getVertexIndex(p3);

    // Tạo hai tam giác
    // Tính hướng mặt sinh ra bởi du × dv
    Vec3 faceDir = du*dv;
    // Nếu faceDir cùng hướng với normal thì dùng winding (i0,i1,i2), ngược lại đảo ngược
    if (  Vec3::multi(faceDir,normal) > 0.0f) {
      // Tam giác (p0,p1,p2) và (p0,p2,p3)
      indices.insert(indices.end(), {
          i0, i1, i2,
          i0, i2, i3
      });
    } else {
      // Đảo winding: (p0,p2,p1) và (p0,p3,p2)
      indices.insert(indices.end(), {
          i0, i2, i1,
          i0, i3, i2
      });
    }
  }

  static void buildMesh(const VoxelGrid &grid, Mesh &mb) {
    int W = grid.width(), H = grid.height(), D = grid.depth();
    for (int z = 0; z < D; ++z)
      for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x) {
          if (!grid.get(x, y, z))
            continue;
          // +X
          if (!grid.get(x + 1, y, z))
            mb.addQuad(Vec3{float(x + 1), float(y), float(z)}, Vec3{1, 0, 0});
          // -X
          if (!grid.get(x - 1, y, z))
            mb.addQuad(Vec3{float(x), float(y), float(z)}, Vec3{-1, 0, 0});
          // +Y
          if (!grid.get(x, y + 1, z))
            mb.addQuad(Vec3{float(x), float(y + 1), float(z)}, Vec3{0, 1, 0});
          // -Y
          if (!grid.get(x, y - 1, z))
            mb.addQuad(Vec3{float(x), float(y), float(z)}, Vec3{0, -1, 0});
          // +Z
          if (!grid.get(x, y, z + 1))
            mb.addQuad(Vec3{float(x), float(y), float(z + 1)}, Vec3{0, 0, 1});
          // -Z
          if (!grid.get(x, y, z - 1))
            mb.addQuad(Vec3{float(x), float(y), float(z)}, Vec3{0, 0, -1});
        }
  }
};
#endif
