#ifndef RAY_HPP
#define RAY_HPP

#include "vector3d.hpp"

namespace rt {

struct Ray {
  Ray() = default;
  Ray(const Point3D& origin, const Vector3D& direction)
      : origin(origin), direction(direction) {}
  [[nodiscard]] Point3D at(double t) const { return origin + t * direction; }
  Point3D origin;
  Vector3D direction;
};

}  // namespace rt

#endif