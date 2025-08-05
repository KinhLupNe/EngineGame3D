#ifndef PLAYER_H
#define PLAYER_H
#include "../../Core/Camera.h"
class Player {
public:
  Camera *cam;
  Vec3 rotation; // góc xoay hiện tại của nó so với gốc//
  Vec3 position;
  Vec3 dir;

  Player();

  ~Player();

  void init(Camera *cam);
  void rotationView(const Vec3 &rotationAngle);
  void move(const Vec3 &direction);
};
#endif
