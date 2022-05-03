#include "sphere.hpp"

namespace rt {

bool Sphere::hit(const Ray& ray, double t_min, double t_max,
                 HitRecord& record) const {
  Vector3D center_to_point{ray.origin - center};
  const double a = ray.direction.length_squared();
  const double half_b = dot_product(center_to_point, ray.direction);
  const double c = center_to_point.length_squared() - radius * radius;
  const double delta = half_b * half_b - a * c;
  if (delta < 0) {
    return false;
  }

  const double delta_sqrt = sqrt(delta);
  double root = (-half_b - delta_sqrt) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + delta_sqrt) / a;
    if (root < t_min || t_max < root) {
      return false;
    }
  }

  record.root = root;
  record.point = ray.at(record.root);
  const Vector3D outward_normal = (record.point - center) / radius;
  record.front_face = dot_product(ray.direction, outward_normal) < 0;
  record.normal = record.front_face ? outward_normal : -outward_normal;
  record.material = material;

  return true;
}

}  // namespace rt