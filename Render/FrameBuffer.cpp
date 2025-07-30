#include "FrameBuffer.h"
FrameBuffer::FrameBuffer(const int &width, const int &height)
    : width(width), height(height) {
  zBuffer.assign(width, vector<float>(height, 100.0f));
  tBuffer.assign(width, vector<char>(height, ' '));
}

void FrameBuffer::clear() {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      tBuffer[i][j] = ' ';
      zBuffer[i][j] = 100.0f;
    }
  }
}
void FrameBuffer::set(int x, int y, float z, char t) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      zBuffer[i][j] = z;
      tBuffer[i][j] = t;
    }
  }
}
void display() {}
