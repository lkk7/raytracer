#include "dielectric.hpp"

namespace rt {

bool Dielectric::scatter(const Ray& ray_in, const HitRecord& rec,
                         ColorRGB& attenuation, Ray& scattered) const {
  attenuation = ColorRGB{1.0, 1.0, 1.0};
  const double refraction_ratio =
      rec.front_face ? (1.0 / refraction_index) : refraction_index;
  Vector3D unit_direction = unit_vector(ray_in.direction);
  const double cos_theta =
      std::fmin(dot_product(-unit_direction, rec.normal), 1.0);
  const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
  bool cannot_refract = refraction_ratio * sin_theta > 1.0;
  Vector3D direction;
  if (cannot_refract ||
      reflectance(cos_theta, refraction_ratio) > random_double()) {
    direction = reflect(unit_direction, rec.normal);
  } else {
    direction = refract(unit_direction, rec.normal, refraction_ratio);
  }
  scattered = Ray{rec.point, direction};
  return true;
}

double Dielectric::reflectance(double cosine, double refraction_ratio) {
  double r0 = ((1.0 - refraction_ratio) / (1.0 + refraction_ratio));
  r0 *= r0;
  return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5.0);
}

}  // namespace rt