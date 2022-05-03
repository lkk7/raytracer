#include "utils.hpp"

#include <random>

namespace rt {

double degrees_to_radians(double degrees) { return degrees * PI / 180.0; }

double random_double() {
  static std::mt19937 engine{std::random_device{}()};
  static std::uniform_real_distribution distribution{0.0, 1.0};
  return distribution(engine);
}

double random_double(double min, double max) {
  return min + (max - min) * random_double();
}

}  // namespace rt
