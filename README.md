# Jeff's Adventure

*A rudimentary platformer starring a personified pencil navigating his way through everyday office settings.*

## Building

To build Jeff's Adventure, you'll need to have [CMake](https://cmake.org/) and [SFML](https://www.sfml-dev.org/) already set up. This project doesn't download SFML for you. If you're using Linux and you've installed SFML through your system package manager, building *should* just work.

If you're on Windows, you'll need to download the [pre-compiled SFML libraries](https://www.sfml-dev.org/download.php) or build SFML yourself. Then you need to copy the correct files into this repository:

- Shared/dynamic libraries (such as DLLs) should go into `bin/`.
- Static libraries (such as `.a` files) should go into `lib/`.
- The SFML include directory should go into `include/`.

Then, you can follow the typical CMake configure and build process. For example, beginning in the project directory:

```shell
mkdir build
cd build
cmake -G Ninja -D CMAKE_BUILD_TYPE=Debug ..
ninja all
```

This example assumes that you have [Ninja](https://ninja-build.org/) installed and that you want to generate debug information (based on `CMAKE_BUILD_TYPE`). Note that by default, installing the project (e.g. `ninja install`) will copy files into an `out/` directory under the CMake build directory.
