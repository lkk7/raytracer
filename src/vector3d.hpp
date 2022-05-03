#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <array>
#include <cmath>
#include <iostream>

#include "utils.hpp"

class Vector3D {
 public:
  Vector3D() : data{0.0, 0.0, 0.0} {}
  Vector3D(double x, double y, double z) : data{x, y, z} {}

  Vector3D operator-() const { return Vector3D(-data[0], -data[1], -data[2]); }
  double operator[](int i) const { return data.at(i); }
  double &operator[](int i) { return data.at(i); }
  Vector3D &operator+=(const Vector3D &other) {
    data[0] += other.data[0];
    data[1] += other.data[1];
    data[2] += other.data[2];
    return *this;
  }
  Vector3D &operator*=(double t) {
    data[0] *= t;
    data[1] *= t;
    data[2] *= t;
    return *this;
  }
  Vector3D &operator/=(double t) { return *this *= 1 / t; }

  [[nodiscard]] double length() const { return std::sqrt(length_squared()); }
  [[nodiscard]] double length_squared() const {
    return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
  }

  [[nodiscard]] bool near_zero() const {
    const auto s = 1e-8;
    return (std::fabs(data[0]) < s) && (std::fabs(data[1]) < s) &&
           (std::fabs(data[2]) < s);
  }

  std::array<double, 3> data;
};

inline Vector3D operator+(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[0] + v2.data[0], v1.data[1] + v2.data[1],
                  v1.data[2] + v2.data[2]);
}

inline Vector3D operator-(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[0] - v2.data[0], v1.data[1] - v2.data[1],
                  v1.data[2] - v2.data[2]);
}

inline Vector3D operator*(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[0] * v2.data[0], v1.data[1] * v2.data[1],
                  v1.data[2] * v2.data[2]);
}

inline Vector3D operator*(double t, const Vector3D &v) {
  return Vector3D(t * v.data[0], t * v.data[1], t * v.data[2]);
}

inline Vector3D operator*(const Vector3D &v, double t) { return t * v; }

inline Vector3D operator/(Vector3D v, double t) { return (1 / t) * v; }

inline std::ostream &operator<<(std::ostream &out, const Vector3D &v) {
  return out << v.data[0] << ' ' << v.data[1] << ' ' << v.data[2];
}

inline double dot_product(const Vector3D &v1, const Vector3D &v2) {
  return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1] +
         v1.data[2] * v2.data[2];
}

inline Vector3D cross_product(const Vector3D &v1, const Vector3D &v2) {
  return Vector3D(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1],
                  v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2],
                  v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]);
}

inline Vector3D unit_vector(Vector3D v) { return v / v.length(); }

inline Vector3D random_vector() {
  return Vector3D{random_double(), random_double(), random_double()};
}

inline Vector3D random_vector(double min, double max) {
  return Vector3D{random_double(min, max), random_double(min, max),
                  random_double(min, max)};
}

inline Vector3D random_in_unit_sphere() {
  while (true) {
    Vector3D random = random_vector(-1.0, 1.0);
    if (random.length_squared() >= 1) {
      continue;
    }
    return random;
  }
}

inline Vector3D random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

inline Vector3D random_in_unit_disk() {
  while (true) {
    auto p = Vector3D{random_double(-1, 1), random_double(-1, 1), 0};
    if (p.length_squared() >= 1) {
      continue;
    }
    return p;
  }
}

inline Vector3D reflect(const Vector3D &v, const Vector3D &normal) {
  return v - 2 * dot_product(v, normal) * normal;
}

inline Vector3D refract(const Vector3D &vector, const Vector3D &normal,
                        double coefficient) {
  double cos_theta = std::fmin(dot_product(-vector, normal), 1.0);
  Vector3D perpendicular = coefficient * (vector + cos_theta * normal);
  Vector3D parallel =
      -std::sqrt(std::fabs(1.0 - perpendicular.length_squared())) * normal;
  return perpendicular + parallel;
}

using Point3D = Vector3D;
using ColorRGB = Vector3D;

#endif