#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include <iostream>

class Vector3D {
 public:
  Vector3D() : data{0, 0, 0} {}
  Vector3D(double x, double y, double z) : data{x, y, z} {}

  Vector3D operator-() const { return Vector3D(-data[0], -data[1], -data[2]); }
  double operator[](int i) const { return data[i]; }
  double &operator[](int i) { return data[i]; }
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

  double length() const { return std::sqrt(length_squared()); }
  double length_squared() const {
    return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
  }

  double data[3];
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

using Point3D = Vector3D;
using ColorRGB = Vector3D;

#endif