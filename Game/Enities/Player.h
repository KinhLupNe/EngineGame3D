/**
 * @file player.h
 * @brief  khao báo lớp player xử lí logic player
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "../../Core/Camera.h"
#define LEFT 1
#define RIGHT 2
#define AHEAD 3
#define BACKWARD 4
#define UP 5
#define DOWN 6

#define LOOK_UP 1
#define LOOK_DOWN 2
#define LOOK_LEFT 3
#define LOOK_RIGHT 4

class Player {
private:
  Camera *cam; // trỏ tới cam của render
  Vec3 rotation; // góc xoay hiện tại của nó so với gốc//
  Vec3 position;
  Vec3 dir; // hướng nhìn

  float spdMove;
  float spdRotate;

public:
  Player();

  ~Player();

  //khởi tạo ban đầu cho player
  void init(Camera *cam);

  // xoay góc nhìn player
  void rotatePlayerView(const int &rotationDir);

  // thay đôi vị trí player
  void move(const int &direction);

  //----------------getter, setter-----------------------------
  Camera *getCam() const {
    return cam;
  }

  void setCam(Camera *cam) {
    this->cam = cam;
  }

  Vec3 getRotation() const {
    return rotation;
  }

  void setRotation(const Vec3 &rotation) {
    this->rotation = rotation;
  }

  Vec3 getPosition() const {
    return position;
  }

  void setPosition(const Vec3 &position) {
    this->position = position;
  }

  Vec3 getDir() const {
    return dir;
  }

  void setDir(const Vec3 &dir) {
    this->dir = dir;
  }

  float getSpd() const {
    return spdMove;
  }

  void setSpd(float spd) {
    this->spdMove = spd;
  }

  float getSpdRotation() const {
    return spdRotate;
  }

  void setSpdRotation(float &spdRotaion) {
    this->spdRotate = spdRotaion;
  }
};
#endif
