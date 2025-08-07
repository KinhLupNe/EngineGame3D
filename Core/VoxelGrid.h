#ifndef VOXELGRID_H
#define VOXELGRID_H
#include "../Game/World/World.h"
#include <vector>

class VoxelGrid {
private:
  int W, H, D;
  std::vector<bool> data;

  inline int index(int x, int y, int z) const {
    return x + y * W + z * (W * H);
  }

  inline bool inBounds(int x, int y, int z) const {
    return x >= 0 && x < W && y >= 0 && y < H && z >= 0 && z < D;
  }

public:
  VoxelGrid(int width, int height, int depth);

  void set(int x, int y, int z, bool solid);

  bool get(int x, int y, int z) const;

  void loadGridFromWord(World *world);

  //---getter, setter-------------------
  int get_w() const {
    return W;
  }

  void set_w(int w) {
    W = w;
  }

  int get_h() const {
    return H;
  }

  void set_h(int h) {
    H = h;
  }

  int get_d() const {
    return D;
  }

  void set_d(int d) {
    D = d;
  }

  std::vector<bool> &get_data() {
    return data;
  }

  void set_data(const std::vector<bool> &data) {
    this->data = data;
  }
};
#endif
