#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "config.hpp"
#include "vector3d.hpp"

namespace rt {

inline constexpr double MAX_COLOR_VALUE = 256.0;

inline void output_color(std::ostream& out, const ColorRGB& c,
                         int samples_per_pixel) {
  double scale = 1.0 / samples_per_pixel;
  const double r = std::sqrt(scale * c[0]);
  const double g = std::sqrt(scale * c[1]);
  const double b = std::sqrt(scale * c[2]);
  out << static_cast<int>(MAX_COLOR_VALUE * std::clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(MAX_COLOR_VALUE * std::clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(MAX_COLOR_VALUE * std::clamp(b, 0.0, 0.999)) << '\n';
}

inline void output_results(
    const std::vector<std::array<ColorRGB, WIDTH>>& results) {
  std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
  for (int j = HEIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < WIDTH; i++) {
      output_color(std::cout, results[j][i], SAMPLES_PER_PIXEL);
    }
  }
}

}  // namespace rt

#endif