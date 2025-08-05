# CGL-Graphics

## Requires
1. OpenGL (version 3.3+)
2. GLAD
3. GLFW
4. GLM
5. Assimp
6. Conan (version 2.0+)


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
