# Raytracer ![language](https://img.shields.io/badge/standard-C++20-blue.svg)

A raytracer from the great book [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html). But it's refactored a lot.

## Example results

![Book example](https://raw.githubusercontent.com/lkk7/raytracer/main/imgs/book.ppm)
![A darker example](https://raw.githubusercontent.com/lkk7/raytracer/main/imgs/dark.ppm)
![A pink example](https://raw.githubusercontent.com/lkk7/raytracer/main/imgs/pink.ppm)

## Installation and usage

No external libraries are needed.

If you just want to quickly check if it works, set a low resolution in `config.hpp`.
Setting `WIDTH = 200` (pixels) should provide an ugly but quick image.
With a standard good width of 1200px, expect several minutes.

```
mkdir build && cd build
cmake ..
make
./raytracer > image.ppm
```

The result should be visible in the `image.ppm` file.
