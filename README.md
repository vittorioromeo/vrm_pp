# vrm_pp [![Build Status](https://travis-ci.org/SuperV1234/vrm_pp.svg?branch=master)](https://travis-ci.org/SuperV1234/vrm_pp)

Small C++ preprocessor library

## Intended usage (quick start)

1. Add this repository and [SuperV1234/vrm_cmake](https://github.com/SuperV1234/vrm_cmake) as submodules of your project, as subfolders in `your_project/extlibs/`:

    ```bash
    git submodule add   https://github.com/SuperV1234/vrm_cmake.git   your_project/extlibs/vrm_cmake
    git submodule add   https://github.com/SuperV1234/vrm_pp.git      your_project/extlibs/vrm_pp
    ```

2. Include `vrm_cmake` in your project's `CMakeLists.txt` and look for the `vrm_pp` extlib:

    ```cmake
    # Include `vrm_cmake`:
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/vrm_cmake/cmake/")
    include(vrm_cmake)

    # Find `vrm_pp`:
    vrm_cmake_find_extlib(vrm_pp)
    ```