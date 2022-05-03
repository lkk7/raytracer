#include "camera.hpp"

#include "hitrecord.hpp"
#include "material.hpp"

namespace rt {

Camera::Camera(Point3D from, Point3D to, Vector3D vup, double vertical_fov_deg,
               double aspect_ratio, double aperture, double focus_distance) {
  const double radians = degrees_to_radians(vertical_fov_deg);
  const double viewport_height = 2.0 * std::tan(radians / 2);
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

Ray Camera::get_ray(double s, double t) const {
  const Point3D random_point = lens_radius * random_in_unit_disk();
  const Point3D offset = u * random_point[0] + v * random_point[1];
  return Ray{origin + offset, lower_left_corner + s * horizontal +
                                  t * vertical - origin - offset};
}

ColorRGB ray_color(const Ray& ray, const SceneObjectList& world, int depth) {
  if (depth <= 0) {
    return ColorRGB{0.0, 0.0, 0.0};
  }
  HitRecord record;
  if (world.hit(ray, 0.001, DOUBLE_INFINITY, record)) {
    Ray scattered;
    ColorRGB attenuation;
    if (record.material->scatter(ray, record, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth - 1);
    }
    return ColorRGB{0.0, 0.0, 0.0};
  }
  Vector3D unit_direction = unit_vector(ray.direction);
  const double t = 0.5 * (unit_direction[1] + 1.0);
  return (1.0 - t) * ColorRGB{1.0, 1.0, 1.0} + t * ColorRGB{0.5, 0.7, 1.0};
}

}  // namespace rt
