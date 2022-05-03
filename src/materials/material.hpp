#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "ray.hpp"
#include "sceneobject.hpp"
#include "vector3d.hpp"

namespace rt {

struct HitRecord;

class Material {
 public:
  Material() = default;
  Material(const Material&) = default;
  Material(Material&&) = default;
  Material& operator=(const Material&) = default;
  Material& operator=(Material&&) = default;
  virtual ~Material() = default;

  virtual bool scatter(const Ray& ray_in, const HitRecord& rec,
                       ColorRGB& attenuation, Ray& scattered) const = 0;
};

}  // namespace rt
#endif