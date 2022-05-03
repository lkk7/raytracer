#include "threadworkload.hpp"

namespace rt {

void thread_workload(const Camera& camera, const SceneObjectList& scene,
                     int row_start, int row_end,
                     std::vector<std::array<ColorRGB, WIDTH>>& result_data) {
  // Set color value of every pixel in the image.
  for (int j = row_start; j < row_end; j++) {
    for (int i = 0; i < WIDTH; i++) {
      ColorRGB color{0.0, 0.0, 0.0};
      for (int s = 0; s < SAMPLES_PER_PIXEL; s++) {
        const double u = (i + random_double()) / (WIDTH - 1);
        const double v = (j + random_double()) / (HEIGHT - 1);
        Ray ray{camera.get_ray(u, v)};
        color += ray_color(ray, scene, MAX_RAY_RECURSION);
      }
      result_data[j][i] = color;
    }
  }
};

std::vector<std::thread> create_threads(
    int n_threads, int rows_per_thread, int rows_remainder,
    const Camera& camera, const SceneObjectList& scene,
    std::vector<std::array<ColorRGB, WIDTH>>& result_data) {
  std::vector<std::thread> threads{};
  for (int i = 0; i < n_threads; i++) {
    double from = i * rows_per_thread;
    double to = (i + 1) * rows_per_thread;
    if (rows_remainder > 0) {
      to += rows_remainder--;
    }
    std::thread work_thread{
        thread_workload,      std::cref(camera), std::cref(scene), from, to,
        std::ref(result_data)};
    threads.emplace_back(std::move(work_thread));
  }
  return threads;
}

}  // namespace rt
