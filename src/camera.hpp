#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include "utils.hpp"
#include "vector3d.hpp"

class Camera {
 public:
  Camera(Point3D from, Point3D to, Vector3D vup, double vertical_fov_deg,
         double aspect_ratio, double aperture, double focus_distance) {
    const double radians = degrees_to_radians(vertical_fov_deg);
    const double h = std::tan(radians / 2);
    const double viewport_height = 2.0 * h;
    const double viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(from - to);
    u = unit_vector(cross_product(vup, w));
    v = cross_product(w, u);

    origin = from;
    horizontal = focus_distance * viewport_width * u;
    vertical = focus_distance * viewport_height * v;
    lower_left_corner =
        origin - horizontal / 2 - vertical / 2 - focus_distance * w;
    lens_radius = aperture / 2;
  }

  Ray get_ray(double s, double t) const {
    const Point3D random_point = lens_radius * random_in_unit_disk();
    const Point3D offset = u * random_point[0] + v * random_point[1];
    return Ray{origin + offset, lower_left_corner + s * horizontal +
                                    t * vertical - origin - offset};
  }

  Point3D origin;
  Point3D lower_left_corner;
  Vector3D horizontal;
  Vector3D vertical;
  Vector3D u, v, w;
  double lens_radius;
};

#endif