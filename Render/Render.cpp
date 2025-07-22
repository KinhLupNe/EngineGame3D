#include "Render.h"
std::vector<Vec2> getLinePoints(Vec3 a, Vec3 b) {
  std::vector<Vec2> result;
  float x1 = a.x, y1 = a.y;
  float x2 = b.x, y2 = b.y;

  float dx = x2 - x1;
  float dy = y2 - y1;

  int steps = std::max(std::abs(dx), std::abs(dy));
  float x_inc = dx / steps;
  float y_inc = dy / steps;

  float x = x1;
  float y = y1;

  for (int i = 0; i <= steps; i++) {
    result.push_back(Vec2{std::round(x), std::round(y)});
    x += x_inc;
    y += y_inc;
  }
  return result;
}
