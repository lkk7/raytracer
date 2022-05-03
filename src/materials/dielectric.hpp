#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "material.hpp"
#include "ray.hpp"
#include "sceneobject.hpp"
#include "vector3d.hpp"

namespace rt {

class Dielectric : public Material {
 public:
  explicit Dielectric(double refraction_index) : refraction_index{refraction_index} {}
  bool scatter(const Ray& ray_in, const HitRecord& rec, ColorRGB& attenuation,
               Ray& scattered) const override;
  static double reflectance(double cosine, double refraction_ratio);

 private:
  double refraction_index;
};

}  // namespace rt
#endif