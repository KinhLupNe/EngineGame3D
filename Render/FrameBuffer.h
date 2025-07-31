#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class FrameBuffer {
private:
  int width;
  int height;
  vector<vector<float>> zBuffer;
  vector<vector<char>> tBuffer;

public:
  FrameBuffer(const int &width, const int &height);
  ~FrameBuffer() = default;
  // reset buffer;
  void clear();
  // set data z-buffer, t-buffer
  void set(int x, int y, float z, char t);
  // convert z-buffer to t-buffer
  static char tBufferFromZBuffer(float z);
  // display buffer
  void display();
  // get
  vector<vector<float>> getZBuffer();
  vector<vector<char>> getTBuffer();
};
#endif
