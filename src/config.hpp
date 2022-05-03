#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "vector3d.hpp"

namespace rt {

constexpr double ASPECT_RATIO = 3.0 / 2.0;
constexpr int WIDTH = 1200;
constexpr int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
constexpr int SAMPLES_PER_PIXEL = 200;
constexpr int MAX_RAY_RECURSION = 50;

/* The camera is located at this point */
constexpr Point3D FROM{13, 2, 3};
/* The camera is pointing at this point */
constexpr Point3D TO{0, 0, 0};
/* A reference vector that indicates where is "up". Probably do not change */
constexpr Vector3D VECTOR_UP{0, 1, 0};
/* Vertical field of view in degrees */
constexpr double VERTICAL_FIELD_OF_VIEW_DEG = 20.0;
/* Distance between the projection point and the plane with perfect focus */
constexpr double FOCUS_DISTANCE = 10.0;
/* Diameter of the "camera hole" */
constexpr double APERTURE = 0.1;

}  // namespace rt

#endif