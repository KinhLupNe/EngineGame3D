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
  spd = 0.2f;
}

void Player::rotationView(const Vec3 &rotationAngle) {
  cam->pitch += rotationAngle.x;
  cam->yaw += rotationAngle.y;
  if (std::abs(cam->pitch) >= 3.14f / 2.0f)
    cam->pitch -= rotationAngle.x;
  rotation = rotation + rotationAngle;
  dir = cam->getForward();
}
void Player::move(const int &direction) {

  Vec3 dir = cam->getForward();
  Vec3 up = Vec3(0, 1, 0);
  Vec3 dirZ = Vec3(dir.x, 0, dir.z).normalize();
  Vec3 dirX = (dirZ * up).normalize();
  if (direction == LEFT) {
    cam->pos = cam->pos - dirX * spd;
  } else if (direction == RIGHT) {
    cam->pos = cam->pos + dirX * spd;
  } else if (direction == AHEAD) {
    cam->pos = cam->pos + dirZ * spd;
  } else if (direction == BACKWARD) {
    cam->pos = cam->pos - dirZ * spd;
  } else if (direction == UP) {
    cam->pos = cam->pos + Vec3(0, 1, 0) * spd;
  } else if (direction == DOWN) {
    cam->pos = cam->pos - Vec3(0, 1, 0) * spd;
  }
  // cam->pos = cam->pos + dirX * 0.2f;
  position = cam->pos;
}
