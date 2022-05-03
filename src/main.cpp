#include <algorithm>
#include <array>
#include <iostream>

#include "camera.hpp"
#include "config.hpp"
#include "dielectric.hpp"
#include "hitrecord.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "output.hpp"
#include "randomscene.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "threadworkload.hpp"
#include "vector3d.hpp"

int main() {
  using namespace rt;
  const Camera camera{
      FROM,         TO,       VECTOR_UP,      VERTICAL_FIELD_OF_VIEW_DEG,
      ASPECT_RATIO, APERTURE, FOCUS_DISTANCE,
  };
  const SceneObjectList scene = get_random_complex_scene();

  // The results are big, so use std::vector to allocate them
  // on heap (otherwise - stack error)
  std::vector<std::array<ColorRGB, WIDTH>> result_data;
  result_data.reserve(HEIGHT);

  int available_threads = static_cast<int>(std::thread::hardware_concurrency());
  available_threads = std::clamp(available_threads, 1, HEIGHT);
  auto [rows_per_thread, rows_remainder] = std::div(HEIGHT, available_threads);
  std::vector<std::thread> threads =
      create_threads(available_threads, rows_per_thread, rows_remainder, camera,
                     scene, result_data);
  std::cerr << "Started tracing with " << available_threads
            << " concurrent thread(s). " << rows_per_thread
            << " rows per thread, remainder: " << rows_remainder
            << " rows split evenly across threads \n";

  // Wait for all threads to finish
  for (auto& thread : threads) {
    thread.join();
  }

  // Output the results in a .ppm format
  output_results(result_data);
  std::cerr << "\nSuccess\n";
}
