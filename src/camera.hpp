#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include "sceneobject.hpp"
#include "utils.hpp"
#include "vector3d.hpp"

namespace rt {

class Camera {
 public:
  Camera(Point3D from, Point3D to, Vector3D vup, double vertical_fov_deg,
         double aspect_ratio, double aperture, double focus_distance);
  [[nodiscard]] Ray get_ray(double s, double t) const;

 private:
  Point3D origin;
  Point3D lower_left_corner;
  Vector3D horizontal;
  Vector3D vertical;
  /* Unit vectors u, v, w are a complete 3D representation
     of the camera's orientation */
  Vector3D u, v, w;
  double lens_radius;
};

ColorRGB ray_color(const Ray& ray, const SceneObjectList& world, int depth);

}  // namespace rt

#endif