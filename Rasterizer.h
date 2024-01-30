#pragma once

#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "geometry.h"
#include "model.h"

namespace rst {
enum class Buffers { Color = 1, Depth = 2 };

enum class Primitive { Line, Triangle };

class rasterizer {
 private:
  Matrix modelMatrix;
  Matrix viewMatrix;
  Matrix projectionMatrix;

  std::vector<float> depth_buffer;

  int width, height;

  std::optional<Texture> texture;

  std::function<Vec3f(fragment_shader_payload)> fragmentShader;
  std::function<Vec3f(vertex_shader_payload)> vertexShader;

  void draw_line();
  void rasterizer_triangle(Triangle& t);

 public:
  rasterizer(int w, int h) : width(w), height(h) {
    frame_buffer.resize(w * h);
    depth_buffer.resize(w * h);

    texture = std::nullopt;
  }

  void set_model(const Matrix& m);
  void set_view(const Matrix& v);
  void set_projection(const Matrix& p);

  void set_texture(Texture tex);

  void clear(Buffers buf);

  void set_pixel(Vec2i& point, Vec3f& color);

  void set_vertexShader(
      std::function<Vec3f(vertex_shader_payload)> vert_shader);
  void set_fragmentShader(
      std::function<Vec3f(fragment_shader_payload)> frag_shader);

  void draw(std::vector<Triangle>& TriangleList);

  std::vector<Vec3f> frame_buffer;
};
}  // namespace rst