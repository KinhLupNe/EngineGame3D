#ifndef VOXELGRID_H
#define VOXELGRID_H
#include "../Game/World/World.h"
#include <cassert>
#include <vector>
class VoxelGrid {
public:
  VoxelGrid(int width, int height, int depth)
      : W(width), H(height), D(depth), data(W * H * D, false) {}

  void set(int x, int y, int z, bool solid) {
    assert(inBounds(x, y, z));
    data[index(x, y, z)] = solid;
  }
  bool get(int x, int y, int z) const {
    if (!inBounds(x, y, z))
      return false;
    return data[index(x, y, z)];
  }
  void loadGridFromWord(World *world) {
    int w = world->getWidth();
    int h = world->getHeight();
    int d = world->getDepth();
    std::vector<Vec3> list = world->getVisualBlockPos();
    for (auto &v : list) {
      this->set(v.x, v.y, v.z, 1);
    }
  }
  int width() const { return W; }
  int height() const { return H; }
  int depth() const { return D; }

private:
  int W, H, D;
  std::vector<bool> data;
  inline int index(int x, int y, int z) const {
    return x + y * W + z * (W * H);
  }
  bool inBounds(int x, int y, int z) const {
    return x >= 0 && x < W && y >= 0 && y < H && z >= 0 && z < D;
  }
};
#endif
