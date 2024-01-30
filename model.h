#pragma once

#include <vector>

#include "Texture.h"
#include "Triangle.h"
#include "geometry.h"
#include "tgaimage.h"

class Model {
 private:
  Texture* tex = nullptr;
  int vertNum, faceNum;

 public:
  std::vector<Triangle> TriangleList;

  Model(const char* filename);
  ~Model();
  int nverts();
  int nfaces();
};