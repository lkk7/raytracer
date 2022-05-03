#include <iostream>

#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "sceneobject.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "vector3d.hpp"

double hit_sphere(const Point3D& center, double radius, const Ray& ray) {
  Vector3D center_to_point = ray.origin - center;
  const double a = ray.direction.length_squared(),
               half_b = dot_product(center_to_point, ray.direction),
               c = center_to_point.length_squared() - radius * radius,
               delta = half_b * half_b - a * c;
  if (delta < 0) {
    return -1.0;
  } else {
    return -half_b - std::sqrt(delta) / a;
  }
}

ColorRGB ray_color(const Ray& ray, const SceneObjectList& world, int depth) {
  if (depth <= 0) return ColorRGB{0.0, 0.0, 0.0};
  HitRecord record;
  if (world.hit(ray, 0.001, infinity, record)) {
    Ray scattered;
    ColorRGB attenuation;
    if (record.material->scatter(ray, record, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);
    return ColorRGB{0.0, 0.0, 0.0};
  }
  Vector3D unit_direction = unit_vector(ray.direction);
  const double t = 0.5 * (unit_direction[1] + 1.0);
  return (1.0 - t) * ColorRGB{1.0, 1.0, 1.0} + t * ColorRGB{0.5, 0.7, 1.0};
}

SceneObjectList random_scene() {
  SceneObjectList world{};

  auto ground_material = std::make_shared<Lambertian>(ColorRGB{0.5, 0.5, 0.5});
  world.add(
      std::make_shared<Sphere>(Point3D{0, -1000, 0}, 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      double choose_material = random_double();
      Point3D center{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};

      if ((center - Point3D{4, 0.2, 0}).length() > 0.9) {
        std::shared_ptr<Material> sphere_material;
        if (choose_material < 0.8) {
          // Lambertian (diffuse/matte)
          auto albedo = random_vector() * random_vector();
          sphere_material = std::make_shared<Lambertian>(albedo);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else if (choose_material < 0.95) {
          // Metal
          Vector3D albedo = random_vector(0.5, 1);
          double fuzz = random_double(0, 0.5);
          sphere_material = std::make_shared<Metal>(albedo, fuzz);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          // Dielectric (glass)
          sphere_material = std::make_shared<Dielectric>(1.5);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }
  auto material1 = std::make_shared<Dielectric>(1.5);
  world.add(std::make_shared<Sphere>(Point3D{0, 1, 0}, 1.0, material1));

  auto material2 = std::make_shared<Lambertian>(ColorRGB{0.4, 0.2, 0.1});
  world.add(std::make_shared<Sphere>(Point3D{-4, 1, 0}, 1.0, material2));

  auto material3 = std::make_shared<Metal>(ColorRGB{0.7, 0.6, 0.5}, 0.0);
  world.add(std::make_shared<Sphere>(Point3D{4, 1, 0}, 1.0, material3));

  return world;
}

int main() {
  constexpr double ASPECT_RATIO = 3.0 / 2.0;
  constexpr int WIDTH = 1200;
  constexpr int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
  constexpr int SAMPLES_PER_PIXEL = 500;
  constexpr int MAX_DEPTH = 50;

  SceneObjectList world = random_scene();

  const Point3D from{13, 2, 3};
  const Point3D to{0, 0, 0};
  const Vector3D vector_up{0, 1, 0};
  const double vertical_field_of_view = 20.0;
  const double focus_distance = 10.0;
  const double aperture = 0.1;
  Camera camera{from,         to,       vector_up,     vertical_field_of_view,
                ASPECT_RATIO, aperture, focus_distance};

  std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
  for (int j = HEIGHT - 1; j >= 0; j--) {
    std::cerr << "Lines left: " << j << '\n';
    for (int i = 0; i < WIDTH; i++) {
      ColorRGB color{0.0, 0.0, 0.0};
      for (int s = 0; s < SAMPLES_PER_PIXEL; s++) {
        const double u = (i + random_double()) / (WIDTH - 1);
        const double v = (j + random_double()) / (HEIGHT - 1);
        Ray ray{camera.get_ray(u, v)};
        color += ray_color(ray, world, MAX_DEPTH);
      }
      output_color(std::cout, color, SAMPLES_PER_PIXEL);
    }
  }
  std::cerr << "Success\n";
}
