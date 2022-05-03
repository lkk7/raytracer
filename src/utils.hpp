#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>
#include <numbers>

namespace rt {

inline constexpr double DOUBLE_INFINITY =
    std::numeric_limits<double>::infinity();
inline constexpr double PI = std::numbers::pi;

double degrees_to_radians(double degrees);

double random_double();

double random_double(double min, double max);

}  // namespace rt

#endif