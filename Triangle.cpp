
#include "Triangle.h"

#include <iostream>

Triangle::Triangle() {
  v[0] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
  v[1] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
  v[2] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

  color[0] = Vec3f();
  color[1] = Vec3f();
  color[2] = Vec3f();

  texCoords[0] = Vec2f();
  texCoords[1] = Vec2f();

  normal[0] = Vec3f();
  normal[1] = Vec3f();
  normal[2] = Vec3f();
}

void Triangle::computeGColor(Vec3f light_dir) {
  for (int i = 0; i < 3; i++) {
    float intensity =
        std::max(0.f, normal[i].normalize() * light_dir.normalize());
    // std::cout << intensity << std::endl;
    color[i] = Vec3f(255, 255, 255) * intensity;
    // std::cout << color[i] << std::endl;
  }
}

void Triangle::computeFcolor(Vec3f light_dir) {
  Vec3f normal_ =
      (Vec3f(v[2].x, v[2].y, v[2].z) - Vec3f(v[0].x, v[0].y, v[0].z)) ^
      (Vec3f(v[1].x, v[1].y, v[1].z) -
       Vec3f(v[0].x, v[0].y, v[0].z));  //计算三角形法线
  normal_.normalize();
  float intensity = std::max(0.f, normal_ * light_dir.normalize());

  for (int i = 0; i < 3; i++) {
    color[i] = Vec3f(255, 255, 255) * intensity;
    // std::cout << color[i] << std::endl;
  }
}