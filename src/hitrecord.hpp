#ifndef HITRECORD_HPP
#define HITRECORD_HPP

#include "vector3d.hpp"

namespace rt {

class Material;

struct HitRecord {
  Point3D point;
  Vector3D normal;
  std::shared_ptr<Material> material;
  double root{};
  bool front_face{};
};

}  // namespace rt

#endif