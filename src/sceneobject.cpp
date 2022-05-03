#include "sceneobject.hpp"

bool SceneObjectList::hit(const Ray& ray, double t_min, double t_max,
                 HitRecord& record) const {
  HitRecord temp;
  bool did_hit = false;
  double closest = t_max;

  for (const auto& object: objects) {
    if (object->hit(ray, t_min, closest, temp)) {
      did_hit = true;
      closest = temp.root;
      record = temp;
    }
  }

  return did_hit;
}
