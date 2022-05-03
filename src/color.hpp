#ifndef COLOR_HPP
#define COLOR_HPP

#include <algorithm>
#include <iostream>

#include "vector3d.hpp"

inline constexpr double MAX_COLOR_VALUE = 256.0;

void output_color(std::ostream& out, const ColorRGB& c, int samples_per_pixel) {
  double scale = 1.0 / samples_per_pixel;
  // sqrt(x) = x^1/2 - adjustment for gamma = 2
  const double r = std::sqrt(scale * c[0]), g = std::sqrt(scale * c[1]),
               b = std::sqrt(scale * c[2]);
  out << static_cast<int>(MAX_COLOR_VALUE * std::clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(MAX_COLOR_VALUE * std::clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(MAX_COLOR_VALUE * std::clamp(b, 0.0, 0.999)) << '\n';
}

#endif