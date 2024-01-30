#pragma once

#include "Texture.h"
#include "geometry.h"

class Triangle {
 private:
 public:
  Vec4f v[3];
  Vec3f normal[3];
  Vec2f texCoords[3];
  Vec3f color[3];

  Triangle();
  void computeGColor(Vec3f light_dir);
  void computeFcolor(Vec3f light_dir);
};
