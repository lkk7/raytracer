#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "material.hpp"
#include "sceneobject.hpp"
#include "vector3d.hpp"

class Sphere : public SceneObject {
 public:
  Sphere() = default;
  Sphere(Point3D cen, double radius, std::unique_ptr<Material>&& material)
      : center{cen}, radius{radius}, material{std::move(material)} {};

  virtual bool hit(const Ray& ray, double t_min, double t_max,
                   HitRecord& rec) const override;

 public:
  Point3D center;
  double radius;
  std::shared_ptr<Material> material;
};

#endif