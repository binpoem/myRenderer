#pragma once

#include "geometry.h"

class Camera {
 private:
 public:
  Vec3f Position;
  Vec3f WorldUp;
  Vec3f Front;
  Vec3f Up;
  Vec3f Right;

  Camera(Vec3f position = Vec3f(0.0f, 0.0f, 0.0f),
         Vec3f worldup = Vec3f(0.f, 1.f, 0.f),
         Vec3f front = Vec3f(0.f, 0.f, -1.f)) {
    Position = position;
    WorldUp = worldup;
    Front = front.normalize();
    Right = (Front ^ WorldUp).normalize();
    Up = (Right ^ Front).normalize();
  }
};