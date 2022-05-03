#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <array>
#include <cmath>
#include <iostream>

#include "utils.hpp"

namespace rt {

class Vector3D {
 public:
  constexpr Vector3D() : data{0.0, 0.0, 0.0} {}
  constexpr Vector3D(double x, double y, double z) : data{x, y, z} {}

  Vector3D operator-() const;
  double operator[](int i) const;
  double &operator[](int i);
  Vector3D &operator+=(const Vector3D &other);
  Vector3D &operator*=(double t);
  Vector3D &operator/=(double t);
  [[nodiscard]] double length() const;
  [[nodiscard]] double length_squared() const;

  std::array<double, 3> data;
};

Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
Vector3D operator*(const Vector3D &v1, const Vector3D &v2);
Vector3D operator*(double t, const Vector3D &v);
Vector3D operator*(const Vector3D &v, double t);
Vector3D operator/(Vector3D v, double t);
std::ostream &operator<<(std::ostream &out, const Vector3D &v);

bool is_near_zero(const Vector3D &v);
double dot_product(const Vector3D &v1, const Vector3D &v2);
Vector3D cross_product(const Vector3D &v1, const Vector3D &v2);
Vector3D unit_vector(Vector3D v);
Vector3D random_vector();
Vector3D random_vector(double min, double max);
Vector3D random_in_unit_sphere();
Vector3D random_unit_vector();
Vector3D random_in_unit_disk();
Vector3D reflect(const Vector3D &v, const Vector3D &normal);
Vector3D refract(const Vector3D &vector, const Vector3D &normal,
                 double coefficient);

using Point3D = Vector3D;
using ColorRGB = Vector3D;

}  // namespace rt

#endif