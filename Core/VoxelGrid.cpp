#include "VoxelGrid.h"
#include <cassert>

VoxelGrid::VoxelGrid(int width, int height, int depth)
    : W(width), H(height), D(depth), data(W * H * D, false) {}

void VoxelGrid::set(int x, int y, int z, bool solid) {
  assert(inBounds(x, y, z));
  data[index(x, y, z)] = solid;
}

bool VoxelGrid::get(int x, int y, int z) const {
  if (!inBounds(x, y, z))
    return false;
  return data[index(x, y, z)];
}

void VoxelGrid::loadGridFromWorld(World *world) {
  // int w = world->getWidth();
  //  int h = world->getHeight();
  // int d = world->getDepth();
  std::vector<Vec3> list = world->getVisualBlockPos();
  for (auto &v : list) {
    this->set(static_cast<int>(v.x), static_cast<int>(v.y),
              static_cast<int>(v.z), true);
  }
}
