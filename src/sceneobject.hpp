#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <memory>
#include <vector>

#include "material.hpp"
#include "ray.hpp"

class Material;

struct HitRecord {
  Point3D point;
  Vector3D normal;
  std::shared_ptr<Material> material;
  double root;
  bool front_face;

  inline void set_face_normal(const Ray& ray, const Vector3D& outward_normal) {
    front_face = dot_product(ray.direction, outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class SceneObject {
 public:
  virtual ~SceneObject() = default;
  virtual bool hit(const Ray& r, double t_min, double t_max,
                   HitRecord& rec) const = 0;
};

class SceneObjectList {
 public:
  SceneObjectList() = default;
  SceneObjectList(std::shared_ptr<SceneObject> object) { add(object); }
  void clear() { objects.clear(); }
  void add(std::shared_ptr<SceneObject> object) { objects.push_back(object); }
  virtual bool hit(const Ray& ray, double t_min, double t_max,
                   HitRecord& rec) const;
  std::vector<std::shared_ptr<SceneObject>> objects;
};

#endif