#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>
#include <numbers>
#include <random>

inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = std::numbers::pi;

constexpr double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  static std::mt19937 engine{std::random_device{}()};
  static std::uniform_real_distribution distribution{0.0, 1.0};
  return distribution(engine);
}

inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}

#endif