#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "vector3d.hpp"

inline constexpr double MAX_COLOR_VALUE = 255.999;

void output_color(std::ostream& out, const ColorRGB& c) {
  out << static_cast<int>(MAX_COLOR_VALUE * c[0]) << ' '
      << static_cast<int>(MAX_COLOR_VALUE * c[1]) << ' '
      << static_cast<int>(MAX_COLOR_VALUE * c[2]) << '\n';
}

#endif