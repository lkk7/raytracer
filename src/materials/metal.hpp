#ifndef METAL_HPP
#define METAL_HPP

#include "material.hpp"
#include "ray.hpp"
#include "sceneobject.hpp"
#include "vector3d.hpp"

namespace rt {

class Metal : public Material {
 public:
  Metal(const ColorRGB& albedo, double fuzz) : albedo{albedo}, fuzz{fuzz} {}
  bool scatter(const Ray& ray_in, const HitRecord& rec, ColorRGB& attenuation,
               Ray& scattered) const override;

 private:
  ColorRGB albedo;
  double fuzz;
};

}  // namespace rt
#endif