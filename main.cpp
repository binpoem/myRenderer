#include <array>
#include <cassert>
#include <iostream>
#include <limits>

#include "Camera.h"
#include "Rasterizer.h"
#include "Shader.h"
#include "model.h"
#include "tgaimage.h"

const int width = 800;
const int height = 800;

Model* model = NULL;

// Vec3f cameraPos(0, 0, 3);  //摄像机摆放的位置
Vec3f lightDir(-10.f, -1.f, -3.f);  //平行光方向
//模型变换矩阵
Matrix modelMatrix() { return Matrix::identity(4); }

Vec3f eye_position(1.f, 1.f, 3.f);  //相机位置
Vec3f center(0.f, 0.f, 0.f);        //相机中心指向center

Camera camera(eye_position, Vec3f(0.f, 1.f, 0.f), center - eye_position);

//视图变换矩阵
Matrix viewMatrix() {
  Matrix view = Matrix::identity(4);
  Matrix r_inverse = Matrix::identity(4);
  Matrix t_inverse = Matrix::identity(4);
  for (int i = 0; i < 3; i++) {
    r_inverse[0][i] = camera.Right[i];
    r_inverse[1][i] = camera.Up[i];
    r_inverse[2][i] = -camera.Front[i];

    t_inverse[i][3] = -camera.Position[i];
  }
  view = r_inverse * t_inverse;
  return view;
}

//透视投影变换矩阵（原作者版本，对照我们上面的公式）
Matrix projectionMatrix() {
  Matrix projection = Matrix::identity(4);
  projection[3][2] = -1.0f / eye_position.z;
  return projection;
}
Vec3f vertex_shader(const vertex_shader_payload& payload) {
  return payload.position;
}
Vec3f normal_fragment_shader(const fragment_shader_payload& payload) {
  Vec3f normal_frag = payload.normal;
  Vec3f return_color =
      (normal_frag.normalize() + Vec3f(1.0f, 1.0f, 1.0f)) * 0.5;

  return Vec3f(return_color.x * 255, return_color.y * 255,
               return_color.z * 255);
}

Vec3f G_fragment_shader(const fragment_shader_payload& payload) {
  Vec3f color_frag = payload.color;
  return color_frag;
}
Vec3f TextureFragmentShader(const fragment_shader_payload& payload) {
  auto texture = payload.texture;
  auto u = payload.tex_coords.x * texture->width;
  auto v = payload.tex_coords.y * texture->height;
  auto intensity = payload.normal * lightDir.normalize() * -1;
  auto tgaColor = payload.texture->getColor(u, v) * intensity;
  return Vec3f(tgaColor.bgra[2], tgaColor.bgra[1], tgaColor.bgra[0]);
}

int main(int argc, char** argv) {
  if (2 == argc) {
    model = new Model(argv[1]);
  } else {
    model = new Model("../obj/african_head.obj");
    // odel = new Model("res/objs/bunny/bunny.obj");
  }

  std::cout << model->nfaces() << "  " << model->nverts() << std::endl;

  //创建TGA图像
  TGAImage image(width, height, TGAImage::Format::RGB);

  //存储所有需要绘制的三角形面片

  //创建光栅化对象
  rst::rasterizer r(width, height);

  //给定纹理并设置
  Texture tex("../obj/african_head_diffuse.tga");
  r.set_texture(tex);

  //清空帧缓冲和zBuffer
  r.clear(rst::Buffers::Color);
  r.clear(rst::Buffers::Depth);

  //设置MVP矩阵
  r.set_model(modelMatrix());
  r.set_view(viewMatrix());
  r.set_projection(projectionMatrix());

  //设置顶点着色器和片元着色器
  r.set_vertexShader(vertex_shader);
  r.set_fragmentShader(TextureFragmentShader);

  //绘制模型
  r.draw(model->TriangleList);

  //将帧缓冲中的颜色值写入image中
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      Vec3f color = r.frame_buffer[j * width + i];
      image.set(i, j, TGAColor(color.x, color.y, color.z, 255));
    }
  }
  image.flip_vertically();
  image.write_tga_file("output.tga");
}