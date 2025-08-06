#ifndef PLAYER_H
#define PLAYER_H
#include "../../Core/Camera.h"
#define LEFT 1
#define RIGHT 2
#define AHEAD 3
#define BACKWARD 4
#define UP 5
#define DOWN 6
class Player {
public:
  Camera *cam;
  Vec3 rotation; // góc xoay hiện tại của nó so với gốc//
  Vec3 position;
  Vec3 dir;
  float spd;
  Player();

  ~Player();

  void init(Camera *cam);
  void rotationView(const Vec3 &rotationAngle);
  void move(const int &direction);
};
#endif
