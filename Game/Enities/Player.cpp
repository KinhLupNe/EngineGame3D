#include "Player.h"
#include "../../Math/Math.h"
#include <cmath>
#include <cstdlib>

Player::Player() { cam = nullptr; }

Player::~Player() = default;

void Player::init(Camera *cam) {
  this->cam = cam;
  rotation = Vec3(cam->pitch, cam->yaw, 0);
  position = cam->pos;
  dir = cam->getForward();
  spdMove = 0.4f;
  spdRotate = 3.14 / 100;
}

/**
 *
 * @param rotationDir hướng xoay
 */
void Player::rotatePlayerView(const int &rotationDir) {
  Vec3 rotationAngle;
  if (rotationDir == LOOK_UP) {
    rotationAngle = Vec3(spdRotate, 0, 0);
  } else if (rotationDir == LOOK_DOWN) {
    rotationAngle = Vec3(-spdRotate, 0, 0);
  } else if (rotationDir == LOOK_LEFT) {
    rotationAngle = Vec3(0, spdRotate, 0);
  } else if (rotationDir == LOOK_RIGHT) {
    rotationAngle = Vec3(0, -spdRotate, 0);
  }
  cam->pitch += rotationAngle.x;
  cam->yaw += rotationAngle.y;
  if (std::abs(cam->pitch) >= 3.14f / 2.0f)
    cam->pitch -= rotationAngle.x;
  rotation = rotation + rotationAngle;
  dir = cam->getForward();
}

/**
 *
 * @param direction
 */
void Player::move(const int &direction) {
  Vec3 dir = cam->getForward();
  Vec3 up = Vec3(0, 1, 0);
  Vec3 dirZ = Vec3(dir.x, 0, dir.z).normalize();
  Vec3 dirX = (dirZ * up).normalize();
  if (direction == LEFT) {
    cam->pos = cam->pos - dirX * spdMove;
  } else if (direction == RIGHT) {
    cam->pos = cam->pos + dirX * spdMove;
  } else if (direction == AHEAD) {
    cam->pos = cam->pos + dirZ * spdMove;
  } else if (direction == BACKWARD) {
    cam->pos = cam->pos - dirZ * spdMove;
  } else if (direction == UP) {
    cam->pos = cam->pos + Vec3(0, 1, 0) * spdMove;
  } else if (direction == DOWN) {
    cam->pos = cam->pos - Vec3(0, 1, 0) * spdMove;
  }

  position = cam->pos;
}
