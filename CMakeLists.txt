cmake_minimum_required(VERSION 3.18)
project(
    "raytracer"
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O2 -fPIC")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SOURCES
    "${SRC_DIR}/camera.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/threadworkload.cpp"
    "${SRC_DIR}/utils.cpp"
    "${SRC_DIR}/vector3d.cpp"
    "${SRC_DIR}/materials/dielectric.cpp"
    "${SRC_DIR}/materials/lambertian.cpp"
    "${SRC_DIR}/materials/metal.cpp"
    "${SRC_DIR}/sceneobjects/randomscene.cpp"
    "${SRC_DIR}/sceneobjects/sceneobject.cpp"
    "${SRC_DIR}/sceneobjects/sphere.cpp"
    )
set(HEADERS
    "${SRC_DIR}/camera.hpp"
    "${SRC_DIR}/config.hpp"
    "${SRC_DIR}/hitrecord.hpp"
    "${SRC_DIR}/output.hpp"
    "${SRC_DIR}/ray.hpp"
    "${SRC_DIR}/threadworkload.hpp"
    "${SRC_DIR}/utils.hpp"
    "${SRC_DIR}/vector3d.hpp"
    "${SRC_DIR}/materials/dielectric.hpp"
    "${SRC_DIR}/materials/lambertian.hpp"
    "${SRC_DIR}/materials/material.hpp"
    "${SRC_DIR}/materials/metal.hpp"
    "${SRC_DIR}/sceneobjects/randomscene.hpp"
    "${SRC_DIR}/sceneobjects/sceneobject.hpp"
    "${SRC_DIR}/sceneobjects/sphere.hpp"
)


add_executable(raytracer ${SOURCES} ${HEADERS})
target_include_directories(raytracer PRIVATE "${SRC_DIR}" "${SRC_DIR}/materials" "${SRC_DIR}/sceneobjects")