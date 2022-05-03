#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "sceneobject.hpp"
#include "vector3d.hpp"

class Sphere : public SceneObject {
 public:
  Sphere() = default;
  Sphere(Point3D cen, double radius) : center{cen}, radius{radius} {};
  virtual ~Sphere() = default;

  virtual bool hit(const Ray& ray, double t_min, double t_max,
                   HitRecord& rec) const override;

 public:
  Point3D center;
  double radius;
};

#endif