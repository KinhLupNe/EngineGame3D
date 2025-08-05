#ifndef WORLD_H
#define WORLD_H
#include "..//..//Math/Math.h"
#include "Block.h"
#include <random>
#include <vector>
class World {

private:
  std::vector<BlockType> data;
  int width, height, depth;

public:
  World() = default;
  World(int width, int height, int depth)
      : width(width), height(height), depth(depth) {
    data.resize(width * height * depth, BlockType::AIR);
  }
  ~World() = default;
  void setBlock(int x, int y, int z, BlockType blockType) {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
      return;
    }
    data[x + y * width + z * width * height] = blockType;
  }
  BlockType getBlock(int x, int y, int z) const {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
      return BlockType::AIR;
    }
    return data[x + y * width + z * width * height];
  }

  void init() {
    for (int i = 0; i < depth; i++) {
      for (int j = 0; j < width; j++) {
        setBlock(j, 0, i, BlockType ::STONE); // Set the ground to stone
      }
    }
  }
  // để kiểm tra xem có block nào không phải là AIR
  std::vector<Vec3> getVisualBlockPos() const {
    std::vector<Vec3> res;
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          if (getBlock(x, y, z) != BlockType::AIR) {
            res.push_back(Vec3(x, y, z));
          }
        }
      }
    }
    return res;
  }

  int getWidth() { return width; }
  int getHeight() { return height; }
  int getDepth() { return depth; }
};
#endif
