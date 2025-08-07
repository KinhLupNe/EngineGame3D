/**
 * @file World.h
 * @brief  Khai báo lớp WORLD xử lý tọa độ của map
 */
#ifndef WORLD_H
#define WORLD_H
#include "..//..//Math/Math.h"
#include "Block.h"
#include <random>
#include <vector>

class World {
private:
  std::vector<BlockType> data;
  // kích thước world
  int width, height, depth;

public:
  World() = default;

  World(int width, int height, int depth);

  ~World() = default;

  // khởi tạo thông số ban đầu cảu world
  void init();

  // gán dữ liệu cho block : loại block, v.v.v
  void setBlock(int x, int y, int z, BlockType blockType);

  // trả về loại block tại vị trí  x,y,z
  BlockType getDataBlock(int x, int y, int z) const;

  // trả về  vị tri các block không phải là AIR trong world
  std::vector<Vec3> getVisualBlockPos() const;

  // ------------getter, setter-----------------------
  const std::vector<BlockType> &getData() const {
    return data;
  }

  void setData(const std::vector<BlockType> &data) {
    this->data = data;
  }

  int getWidth() const {
    return width;
  }

  void setWidth(int width) {
    this->width = width;
  }

  int getHeight() const {
    return height;
  }

  void setHeight(int height) {
    this->height = height;
  }

  int getDepth() const {
    return depth;
  }

  void setDepth(int depth) {
    this->depth = depth;
  }
};
#endif
