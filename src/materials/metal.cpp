#include "metal.hpp"

namespace rt {

bool Metal::scatter(const Ray& ray_in, const HitRecord& rec,
                    ColorRGB& attenuation, Ray& scattered) const {
  Vector3D reflected = reflect(unit_vector(ray_in.direction), rec.normal);
  scattered = Ray{rec.point, reflected + fuzz * random_in_unit_sphere()};
  attenuation = albedo;
  return (dot_product(scattered.direction, rec.normal) > 0);
}

}  // namespace rt