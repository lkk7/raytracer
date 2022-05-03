#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "material.hpp"
#include "ray.hpp"
#include "sceneobject.hpp"
#include "vector3d.hpp"

namespace rt {

class Lambertian : public Material {
 public:
  explicit Lambertian(const ColorRGB& albedo) : albedo{albedo} {}
  bool scatter(const Ray& ray_in, const HitRecord& rec, ColorRGB& attenuation,
               Ray& scattered) const override;

 private:
  ColorRGB albedo;
};

}  // namespace rt
#endif