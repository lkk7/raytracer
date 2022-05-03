#include "lambertian.hpp"

namespace rt {

bool Lambertian::scatter([[maybe_unused]] const Ray& ray_in,
                         const HitRecord& rec, ColorRGB& attenuation,
                         Ray& scattered) const {
  Vector3D scatter_direction = rec.normal + random_unit_vector();
  if (is_near_zero(scatter_direction)) {
    scatter_direction = rec.normal;
  }
  scattered = Ray(rec.point, scatter_direction);
  attenuation = albedo;
  return true;
}

}  // namespace rt