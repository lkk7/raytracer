#include <algorithm>
#include <array>
#include <iostream>
#include <thread>

#include "camera.hpp"
#include "material.hpp"
#include "output.hpp"
#include "ray.hpp"
#include "sceneobject.hpp"
#include "sphere.hpp"
#include "vector3d.hpp"

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

  auto ground_material = std::make_unique<Lambertian>(ColorRGB{0.5, 0.5, 0.5});
  world.add(std::make_unique<Sphere>(Point3D{0, -1000, 0}, 1000,
                                     std::move(ground_material)));

  auto material1 = std::make_unique<Dielectric>(1.5);
  auto material2 = std::make_unique<Lambertian>(ColorRGB{0.4, 0.2, 0.1});
  auto material3 = std::make_unique<Metal>(ColorRGB{0.7, 0.6, 0.5}, 0.0);
  world.add(
      std::make_unique<Sphere>(Point3D{0, 1, 0}, 1.0, std::move(material1)));
  world.add(
      std::make_unique<Sphere>(Point3D{-4, 1, 0}, 1.0, std::move(material2)));
  world.add(
      std::make_unique<Sphere>(Point3D{4, 1, 0}, 1.0, std::move(material3)));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      double choose_material = random_double();
      Point3D center{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};

      if ((center - Point3D{4, 0.2, 0}).length() > 0.9) {
        std::unique_ptr<Material> sphere_material;
        if (choose_material < 0.8) {
          // Lambertian (diffuse/matte)
          auto albedo = random_vector() * random_vector();
          sphere_material = std::make_unique<Lambertian>(albedo);
          world.add(std::make_unique<Sphere>(center, 0.2,
                                             std::move(sphere_material)));
        } else if (choose_material < 0.95) {
          // Metal
          Vector3D albedo = random_vector(0.5, 1);
          double fuzz = random_double(0, 0.5);
          sphere_material = std::make_unique<Metal>(albedo, fuzz);
          world.add(std::make_unique<Sphere>(center, 0.2,
                                             std::move(sphere_material)));
        } else {
          // Dielectric (glass)
          sphere_material = std::make_unique<Dielectric>(1.5);
          world.add(std::make_unique<Sphere>(center, 0.2,
                                             std::move(sphere_material)));
        }
      }
    }
  }

  return world;
}

int main() {
  constexpr double ASPECT_RATIO = 3.0 / 2.0;
  constexpr int WIDTH = 400;
  constexpr int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
  constexpr int SAMPLES_PER_PIXEL = 100;
  constexpr int MAX_DEPTH = 50;

  SceneObjectList world = random_scene();

  const Point3D from{13, 2, 3};
  const Point3D to{0, 0, 0};
  const Vector3D vector_up{0, 1, 0};
  const double vertical_field_of_view = 20.0;
  const double focus_distance = 10.0;
  const double aperture = 0.1;
  const Camera camera{
      from,         to,       vector_up,     vertical_field_of_view,
      ASPECT_RATIO, aperture, focus_distance};

  // std::vector to allocate elements on heap
  std::vector<std::array<ColorRGB, WIDTH>> result_data;
  result_data.reserve(HEIGHT);

  int available_threads = std::thread::hardware_concurrency();
  available_threads = std::clamp(available_threads, 1, HEIGHT);
  auto [rows_per_thread, rows_remainder] = std::div(HEIGHT, available_threads);
  std::cerr << "Starting with " << available_threads
            << " concurrent thread(s). " << rows_per_thread
            << " rows per thread, remainder: " << rows_remainder
            << " rows split evenly across threads \n";

  auto thread_workload = [&world = std::as_const(world),
                          &camera = std::as_const(camera),
                          &result_data](int row_start, int row_end) {
    for (int j = row_start; j < row_end; j++) {
      for (int i = 0; i < WIDTH; i++) {
        ColorRGB color{0.0, 0.0, 0.0};
        for (int s = 0; s < SAMPLES_PER_PIXEL; s++) {
          const double u = (i + random_double()) / (WIDTH - 1);
          const double v = (j + random_double()) / (HEIGHT - 1);
          Ray ray{camera.get_ray(u, v)};
          color += ray_color(ray, world, MAX_DEPTH);
        }
        result_data[j][i] = color;
      }
    }
  };

  std::vector<std::thread> threads;
  for (int i = 0; i < available_threads; i++) {
    double from = i * rows_per_thread;
    double to = (i + 1) * rows_per_thread;
    if (rows_remainder > 0) to += rows_remainder--;
    std::thread work_thread{thread_workload, from, to};
    threads.emplace_back(std::move(work_thread));
  }

  for (auto& thread : threads) {
    thread.join();
  }

  std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
  for (int j = HEIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < WIDTH; i++) {
      output_color(std::cout, result_data[j][i], SAMPLES_PER_PIXEL);
    }
  }
  std::cerr << "\nSuccess\n";
}
