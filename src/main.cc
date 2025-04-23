#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
#include <chrono>

color ray_color(const ray &r) {
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5*(unit_direction.y() + 1.0);
  return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  // Image Info

  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera

  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width)/image_height);
  auto camera_center = vec3(0, 0, 0);

  //vectors across horizontal and vertical viewport edges

  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // horizontal and vertical delta vectors from pixel to pixel
  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  // location of upper left pixel
  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
  auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Render

  std::cout << "P3\n";
  std::cout << image_width; 
  std::cout << ' ';
  std::cout << image_height; 
  std::cout << "\n255" << std::endl;

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      // center of pixel to accurately calculate the distance where the ray is coming from
      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

      // now we calculate the ray direction
      auto ray_direction = pixel_center - camera_center;
      // now we create the ray from the camera center given direction to the pixel
      ray r(camera_center, ray_direction);

      // color the pixel accordingly
      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << std::endl;
  std::clog << "\rDone." << std::endl;

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::clog << "Elapsed Time:" << elapsed.count() << " seconds." << std::endl;
}
