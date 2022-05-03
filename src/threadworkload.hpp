#ifndef THREADWORKLOAD_HPP
#define THREADWORKLOAD_HPP

#include <thread>

#include "camera.hpp"
#include "config.hpp"
#include "ray.hpp"
#include "sceneobject.hpp"
#include "vector3d.hpp"

namespace rt {

void thread_workload(const Camera& camera, const SceneObjectList& scene,
                     int row_start, int row_end,
                     std::vector<std::array<ColorRGB, WIDTH>>& result_data);

std::vector<std::thread> create_threads(
    int n_threads, int rows_per_thread, int rows_remainder,
    const Camera& camera, const SceneObjectList& scene,
    std::vector<std::array<ColorRGB, WIDTH>>& result_data);

}  // namespace rt

#endif