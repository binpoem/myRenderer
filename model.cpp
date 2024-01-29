#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Model::Model(const char* filename, const char* textureFilepath)
    : verts_(), faces_(), texture_(new TGAImage()) {
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail()) return;
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      Vec3f v;
      for (int i = 0; i < 3; i++) iss >> v.raw[i];
      verts_.push_back(v);
    } else if (!line.compare(0, 3, "vn ")) {
      iss >> trash >> trash;
      Vec3f n;
      for (int i = 0; i < 3; i++) iss >> n.raw[i];
      norms_.push_back(n);
    } else if (!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      Vec2f uv;
      for (int i = 0; i < 2; i++) iss >> uv.raw[i];
      int t;
      iss >> t;
      uvs_.push_back(uv);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<Vec3i> f;
      int itrash, idx[3];
      iss >> trash;
      while (iss >> idx[0] >> trash >> idx[1] >> trash >> idx[2]) {
        for (int i = 0; i < 3; ++i) {
          idx[i]--;
        };  // in wavefront obj all indices start at 1, not zero
        f.push_back(Vec3i{idx[0], idx[1], idx[2]});
      }
      faces_.push_back(f);
    }
  }
  std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
  texture_->read_tga_file(textureFilepath);
  texture_->flip_vertically();
}

Model::~Model() {}

int Model::nverts() { return (int)verts_.size(); }

int Model::nfaces() { return (int)faces_.size(); }

std::vector<Vec3i>& Model::face(int idx) { return faces_[idx]; }

Vec3f Model::vert(int i) { return verts_[i]; }
Vec2f Model::uv(int idx) { return uvs_[idx]; }
Vec3f Model::norm(int idx) { return norms_[idx]; }
TGAColor Model::diffuse(Vec2f uv) {
  return texture_->get(uv.u * texture_->get_width(),
                       uv.v * texture_->get_height());
}