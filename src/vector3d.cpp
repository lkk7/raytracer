#include "vector3d.hpp"

namespace rt {

Vector3D Vector3D::operator-() const {
  return Vector3D(-data[0], -data[1], -data[2]);
}

double Vector3D::operator[](int i) const { return data[i]; }

double &Vector3D::operator[](int i) { return data[i]; }

Vector3D &Vector3D::operator+=(const Vector3D &other) {
  data[0] += other.data[0];
  data[1] += other.data[1];
  data[2] += other.data[2];
  return *this;
}

Vector3D &Vector3D::operator*=(double t) {
  data[0] *= t;
  data[1] *= t;
  data[2] *= t;
  return *this;
}

Vector3D &Vector3D::operator/=(double t) { return *this *= 1 / t; }

double Vector3D::length() const { return std::sqrt(length_squared()); }

double Vector3D::length_squared() const {
  return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

Vector3D operator+(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[0] + v2.data[0], v1.data[1] + v2.data[1],
                  v1.data[2] + v2.data[2]);
}

Vector3D operator-(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[0] - v2.data[0], v1.data[1] - v2.data[1],
                  v1.data[2] - v2.data[2]);
}

Vector3D operator*(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[0] * v2.data[0], v1.data[1] * v2.data[1],
                  v1.data[2] * v2.data[2]);
}

Vector3D operator*(double t, const Vector3D &v) {
  return Vector3D(t * v.data[0], t * v.data[1], t * v.data[2]);
}

Vector3D operator*(const Vector3D &v, double t) { return t * v; }

Vector3D operator/(Vector3D v, double t) { return (1 / t) * v; }

std::ostream &operator<<(std::ostream &out, const Vector3D &v) {
  return out << v.data[0] << ' ' << v.data[1] << ' ' << v.data[2];
}

bool is_near_zero(const Vector3D &v) {
  static constexpr double s = 1e-8;
  return (std::fabs(v.data[0]) < s) && (std::fabs(v.data[1]) < s) &&
         (std::fabs(v.data[2]) < s);
}

double dot_product(const Vector3D &v1, const Vector3D &v2) {
  return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1] +
         v1.data[2] * v2.data[2];
}

Vector3D cross_product(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1],
                  v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2],
                  v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]);
}

Vector3D unit_vector(Vector3D v) { return v / v.length(); }

Vector3D random_vector() {
  return Vector3D{random_double(), random_double(), random_double()};
}

Vector3D random_vector(double min, double max) {
  return Vector3D{random_double(min, max), random_double(min, max),
                  random_double(min, max)};
}

Vector3D random_in_unit_sphere() {
  while (true) {
    Vector3D random = random_vector(-1.0, 1.0);
    if (random.length_squared() >= 1) {
      continue;
    }
    return random;
  }
}

Vector3D random_unit_vector() { return unit_vector(random_in_unit_sphere()); }

Vector3D random_in_unit_disk() {
  while (true) {
    auto p = Vector3D{random_double(-1, 1), random_double(-1, 1), 0};
    if (p.length_squared() >= 1) {
      continue;
    }
    return p;
  }
}

Vector3D reflect(const Vector3D &v, const Vector3D &normal) {
  return v - 2 * dot_product(v, normal) * normal;
}

Vector3D refract(const Vector3D &vector, const Vector3D &normal,
                 double coefficient) {
  double cos_theta = std::fmin(dot_product(-vector, normal), 1.0);
  Vector3D perpendicular = coefficient * (vector + cos_theta * normal);
  Vector3D parallel =
      -std::sqrt(std::fabs(1.0 - perpendicular.length_squared())) * normal;
  return perpendicular + parallel;
}

}  // namespace rt
