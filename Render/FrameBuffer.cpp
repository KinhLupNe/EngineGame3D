#include "FrameBuffer.h"
#include <ostream>
#include <string>
#include <iostream>

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
  char tList[] = "@n*;:,.";

  int l = sizeof(tList) / sizeof(char);
  float step = 1.0f / static_cast<float>(l);
  char t = tList[static_cast<int>(z / step)];
  return t;
}

void FrameBuffer::set(int x, int y, float z, char t) {
  zBuffer[y][x] = z;
  tBuffer[y][x] = t;
}

void FrameBuffer::putText(int x, int y, const std::string &text) {
  if (y < 0 || y >= height)
    return;
  for (size_t i = 0; i < text.size(); ++i) {
    int xx = x + static_cast<int>(i);
    if (xx < 0 || xx >= width)
      break;
    tBuffer[y][xx] = text[i];
  }
}

void FrameBuffer::display() const {
  std::string frame;
  frame.reserve(height * (width + 1));
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      frame.push_back(tBuffer[this->height - 1 - i][j]);
    }
    frame.push_back('\n');
  }
  frame.pop_back();
  std::cout << "\x1b[H" << frame << std::flush;
}


