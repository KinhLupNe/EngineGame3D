#ifndef CAMERA_H
#define CAMERA_H
#include "../Math/Math.h"
class Camera {
public:
  Vec3 pos;    // Camera position
  float yaw;   // Horizontal angle (radians)
  float pitch; // Vertical angle (radians)
  float zNear; // Near clipping plane
  float zFar;  // Far clipping plane
  float aspect;
  float fovY; // Frustum bounds: left, right, bottom, top

  Camera(Vec3 pos = Vec3{0.0f, 0.0f, 0.0f}, float yaw = 0.0f,
         float pitch = 0.0f, float zNear = 0.1f, float zFar = 100.0f,
         float aspect = 140 / 600, float fovY = 3.14 / 3);

  // Returns view matrix from position and yaw/pitch
  Mat4 getViewMatrix() const;

  // Returns projection matrix defined by frustum
  Mat4 getProjectionMatrix() const;

  Vec3 getForward() const;
};

#endif
