cmake_minimum_required(VERSION 3.18)
project(
    "raytracer"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O2 -fPIC")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SOURCES
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/sceneobject.cpp"
    "${SRC_DIR}/sphere.cpp"
    )
set(HEADERS
    "${SRC_DIR}/color.hpp"
    "${SRC_DIR}/ray.hpp"
    "${SRC_DIR}/sceneobject.hpp"
    "${SRC_DIR}/sphere.hpp"
    "${SRC_DIR}/utils.hpp"
    "${SRC_DIR}/vector3d.hpp"
)

add_executable(raytracer ${SOURCES} ${HEADERS})
