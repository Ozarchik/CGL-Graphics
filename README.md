# CGL-Graphics
[![Windows](https://github.com/Ozarchik/CGL-Graphics/actions/workflows/cmake-windows.yml/badge.svg)](https://github.com/Ozarchik/CGL-Graphics/actions/workflows/cmake-windows.yml)
## Requires
1. C++20
2. OpenGL (version 3.3+)
3. GLAD
4. GLFW
5. GLM
6. Assimp
7. Conan (version 2.0+)


## How to build
1. run conan install

   ```bash
   conan install . -pr:a <conan_profile> -b missing
   ```

3. run cmake configure and build

   ```bash
   cmake --preset conan-<build_type>
   cmake --build --preset conan-<build_type>
   ```
