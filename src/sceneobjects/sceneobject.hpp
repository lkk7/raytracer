#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <memory>
#include <vector>

#include "hitrecord.hpp"
#include "ray.hpp"

namespace rt {

class SceneObject {
 public:
  SceneObject() = default;
  SceneObject(const SceneObject&) = default;
  SceneObject(SceneObject&&) = default;
  SceneObject& operator=(const SceneObject&) = default;
  SceneObject& operator=(SceneObject&&) = default;
  virtual ~SceneObject() = default;
  virtual bool hit(const Ray& r, double t_min, double t_max,
                   HitRecord& rec) const = 0;
};

class SceneObjectList {
 public:
  SceneObjectList() = default;
  void clear() { objects.clear(); }
  void add(std::unique_ptr<SceneObject>&& object) {
    objects.emplace_back(std::move(object));
  }
  virtual bool hit(const Ray& ray, double t_min, double t_max,
                   HitRecord& rec) const;
  std::vector<std::unique_ptr<SceneObject>> objects;
};

}  // namespace rt

#endif