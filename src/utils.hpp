#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>
#include <numbers>

inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = std::numbers::pi;

constexpr double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

#endif