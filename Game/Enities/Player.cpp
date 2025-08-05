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
}

void Player::rotationView(const Vec3 &rotationAngle) {
  cam->pitch += rotationAngle.x;
  cam->yaw += rotationAngle.y;
  rotation = rotation + rotationAngle;
  dir = cam->getForward();
}
void Player::move(const Vec3 &direction) {
  Vec4 dis = Vec4(cam->pos.x, cam->pos.y, cam->pos.z, 1);
  Vec4 dir = Vec4(direction.x, direction.y, direction.z, 1);
  Mat4 R = Mat4::getRotationMatrix(Vec3(0, cam->yaw, 0));
  dis = (R * dir);
  cam->pos = cam->pos + Vec3(dis.x, dis.y, dis.z);
  position = cam->pos;
}
