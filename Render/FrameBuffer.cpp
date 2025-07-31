#include "FrameBuffer.h"
#include <ostream>
#include <string>
FrameBuffer::FrameBuffer(const int &width, const int &height)
    : width(width), height(height) {
  zBuffer.assign(height, vector<float>(width, 100.0f));
  tBuffer.assign(height, vector<char>(width, ' '));
}

void FrameBuffer::clear() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      tBuffer[i][j] = ' ';
      zBuffer[i][j] = 100.0f;
    }
  }
}
char FrameBuffer::tBufferFromZBuffer(float z) {
  char tList[] = " `.-':_,^=;><+!rc*/"
                 "z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]"
                 "2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

  int l = sizeof(tList) / sizeof(char);
  float step = 1.0f / (float)(l);
  char t = tList[(int)(z / step)];
  return t;
}
void FrameBuffer::set(int x, int y, float z, char t) {
  zBuffer[y][x] = z;
  tBuffer[y][x] = t;
}
void FrameBuffer::display() {
  std::string frame;
  frame.reserve(height * (width + 1));
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      frame.push_back(tBuffer[i][j]);
    }
    frame.push_back('\n');
  }
  std::cout << "\x1b[H" << frame << std::flush;
}
vector<vector<float>> FrameBuffer::getZBuffer() { return zBuffer; }
vector<vector<char>> FrameBuffer::getTBuffer() { return tBuffer; }
