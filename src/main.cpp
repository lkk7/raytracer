#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "sceneobject.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "vector3d.hpp"

double hit_sphere(const Point3D& center, double radius, const Ray& ray) {
  Vector3D center_to_point = ray.origin - center;
  double a = ray.direction.length_squared(),
         half_b = dot_product(center_to_point, ray.direction),
         c = center_to_point.length_squared() - radius * radius,
         delta = half_b * half_b - a * c;
  if (delta < 0) {
    return -1.0;
  } else {
    return -half_b - std::sqrt(delta) / a;
  }
}

ColorRGB ray_color(const Ray& ray, const SceneObjectList& world) {
  HitRecord record;
  if (world.hit(ray, 0, infinity, record)) {
    return 0.5 * (record.normal + ColorRGB{1, 1, 1});
  }
  Vector3D unit_direction = unit_vector(ray.direction);
  // Scale from (-1, 1) to (0, 1)
  double t = 0.5 * (unit_direction[1] + 1.0);
  return (1.0 - t) * ColorRGB{1.0, 1.0, 1.0} + t * ColorRGB{0.5, 0.7, 1.0};
}

int main() {
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr int WIDTH = 400;
  constexpr int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

  constexpr double VIEWPORT_HEIGHT = 2.0;
  constexpr double VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
  constexpr double FOCAL_LENGTH = 1.0;
  Point3D origin = Point3D{0, 0, 0};
  Vector3D horizontal = Point3D{VIEWPORT_WIDTH, 0, 0};
  Vector3D vertical = Point3D{0, VIEWPORT_HEIGHT, 0};
  Point3D lower_left_corner =
      origin - horizontal / 2 - vertical / 2 - Point3D(0, 0, FOCAL_LENGTH);

  SceneObjectList world{};
  world.add(std::make_shared<Sphere>(Point3D{0, 0, -1}, 0.5));
  world.add(std::make_shared<Sphere>(Point3D{0, -100.5, -1}, 100));

  std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
  for (int j = HEIGHT - 1; j >= 0; j--) {
    std::cerr << "Lines left: " << j << '\n';
    for (int i = 0; i < WIDTH; i++) {
      auto u = double(i) / (WIDTH - 1);
      auto v = double(j) / (HEIGHT - 1);
      Ray ray{origin,
              lower_left_corner + u * horizontal + v * vertical - origin};
      ColorRGB pixel = ray_color(ray, world);
      output_color(std::cout, pixel);
    }
  }
  std::cerr << "Success\n";
}
