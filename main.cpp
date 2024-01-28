#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

// !First attempt
// void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
//   for (float t = 0.; t < 1.; t += .01) {
//     int x = x0 + (x1 - x0) * t;
//     int y = y0 + (y1 - y0) * t;
//     image.set(x, y, color);
//   }
// }
// !Second attempt
// void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
//   for (int x = x0; x <= x1; x++) {
//     float t = (x - x0) / (float)(x1 - x0);
//     int y = y0 * (1. - t) + y1 * t;
//     image.set(x, y, color);
//   }
// }

// !Third attempt
// void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
//   bool steep = false;
//   if (std::abs(x0 - x1) <
//       std::abs(y0 - y1)) {  // if the line is steep, we transpose the image
//     std::swap(x0, y0);
//     std::swap(x1, y1);
//     steep = true;
//   }
//   if (x0 > x1) {  // make it left−to−right
//     std::swap(x0, x1);
//     std::swap(y0, y1);
//   }
//   for (int x = x0; x <= x1; x++) {
//     float t = (x - x0) / (float)(x1 - x0);
//     int y = y0 * (1. - t) + y1 * t;
//     if (steep) {
//       image.set(y, x, color);  // if transposed, de−transpose
//     } else {
//       image.set(x, y, color);
//     }
//   }
// }
// !Fourth attempt continued
// void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
//   bool steep = false;
//   if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
//     std::swap(x0, y0);
//     std::swap(x1, y1);
//     steep = true;
//   }
//   if (x0 > x1) {
//     std::swap(x0, x1);
//     std::swap(y0, y1);
//   }
//   int dx = x1 - x0;
//   int dy = y1 - y0;
//   float derror = std::abs(dy / float(dx));
//   float error = 0;
//   int y = y0;
//   for (int x = x0; x <= x1; x++) {
//     if (steep) {
//       image.set(y, x, color);
//     } else {
//       image.set(x, y, color);
//     }
//     error += derror;
//     if (error > .5) {
//       y += (y1 > y0 ? 1 : -1);
//       error -= 1.;
//     }
//   }
// }
// !Timings: fifth and final attempt
void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
  bool steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
  int dx = x1 - x0;
  int dy = y1 - y0;
  int derror2 = std::abs(dy) * 2;
  int error2 = 0;
  int y = y0;
  for (int x = x0; x <= x1; x++) {
    if (steep) {
      image.set(y, x, color);
    } else {
      image.set(x, y, color);
    }
    error2 += derror2;
    if (error2 > dx) {
      y += (y1 > y0 ? 1 : -1);
      error2 -= dx * 2;
    }
  }
}

int main(int argc, char** argv) {
  TGAImage image(100, 100, TGAImage::RGB);
  line(13, 20, 80, 40, image, white);
  line(20, 13, 40, 80, image, red);
  line(80, 40, 13, 20, image, red);
  image.flip_vertically();
  image.write_tga_file("output.tga");
  return 0;
}