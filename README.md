# README

### 1. What is this?

A simple application to trigger windows 10 tablet mode.

#### Building

In project folder:

For debugging purposes:

1. mkdir build && cd build
2. conan install .. -s build_type=Debug  --build=missing -s compiler="Visual Studio" -s compiler.runtime="MDd"
3. cmake -G "Visual Studio 15 Win64" -DCMAKE_BUILD_TESTS=ON ..
4. cmake --build . --target ALL_BUILD --config Debug

For building a release version:

1. mkdir build && cd build
2. conan install .. -s build_type=Release  --build=missing
3. cmake -G "Visual Studio 15 Win64" -DCMAKE_BUILD_TESTS=ON ..
4. cmake --build . --target ALL_BUILD --config Release

