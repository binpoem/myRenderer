#ifndef __MODEL_H__
#define __MODEL_H__

#include <tgaimage.h>

#include <vector>

#include "geometry.h"

class Model {
 private:
  std::vector<Vec3f> verts_;
  std::vector<Vec3f> norms_;
  std::vector<Vec2f> uvs_;

  std::vector<std::vector<Vec3i> > faces_;
  TGAImage* texture_{nullptr};

 public:
  Model(const char* filename, const char* textureFilepath);
  ~Model();
  int nverts();
  int nfaces();
  Vec3f vert(int i);
  Vec2f uv(int idx);
  Vec3f norm(int idx);
  std::vector<Vec3i>& face(int idx);
  TGAColor diffuse(Vec2f uv);
};

#endif  //__MODEL_H__
