#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "ray.hpp"
#include "sceneobject.hpp"
#include "vector3d.hpp"

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

class Lambertian : public Material {
 public:
  Lambertian(const ColorRGB& albedo) : albedo{albedo} {}
  bool scatter([[maybe_unused]] const Ray& ray_in, const HitRecord& rec,
               ColorRGB& attenuation, Ray& scattered) const override;

  ColorRGB albedo;
};

class Metal : public Material {
 public:
  Metal(const ColorRGB& albedo, double fuzz) : albedo{albedo}, fuzz{fuzz} {}
  bool scatter(const Ray& ray_in, const HitRecord& rec, ColorRGB& attenuation,
               Ray& scattered) const override;

  ColorRGB albedo;
  double fuzz;
};

class Dielectric : public Material {
 public:
  Dielectric(double refraction_index) : refraction_index{refraction_index} {}
  bool scatter(const Ray& ray_in, const HitRecord& rec, ColorRGB& attenuation,
               Ray& scattered) const override;
  static double reflectance(double cosine, double refraction_ratio);

  double refraction_index;
};

#endif