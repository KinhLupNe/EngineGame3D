#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class FrameBuffer {
private:
  int width;
  int height;
  vector<vector<float> > zBuffer;
  vector<vector<char> > tBuffer;

public:
  FrameBuffer() = default;

  FrameBuffer(const int &width, const int &height);

  ~FrameBuffer() = default;

  // reset buffer;
  void clear();

  // set data z-buffer, t-buffer
  void set(int x, int y, float z, char t);

  // convert z-buffer to t-buffer
  static char tBufferFromZBuffer(float z);

  // put text to t-Buffer
  void putText(int x, int y, const std::string &text);

  // put data to t-Buffer
  template<typename... Args>
  void put(int x, int y, Args &&... args) {
    std::ostringstream oss;
    (oss << ... << args); // C++17 fold expression
    putText(x, y, oss.str());
  }

  // display buffer
  void display() const;

  // -----setter, getter-----------------


  int getWidth() const {
    return width;
  }

  void setWidth(int width) {
    this->width = width;
  }

  int getWeight() const {
    return height;
  }

  void setHeight(int height) {
    this->height = height;
  }

  vector<vector<float> > &getZBuffer() {
    return zBuffer;
  }

  void setZBuffer(const vector<vector<float> > &z_buffer) {
    zBuffer = z_buffer;
  }

  vector<vector<char> > &t_buffer() {
    return tBuffer;
  }

  void set_t_buffer(const vector<vector<char> > &t_buffer) {
    tBuffer = t_buffer;
  }
};
#endif
