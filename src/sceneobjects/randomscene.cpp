#include "dielectric.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "sceneobject.hpp"
#include "sphere.hpp"

namespace rt {

SceneObjectList get_random_complex_scene() {
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

}  // namespace rt