# CGL-Graphics

## Requires
1. Assimp
2. GLEW
3. GLFW
4. GLM
5. Conan (version 2.0+)
## How to build

1. run conan install
   conan install . -pr:a <conan_profile> -b missing

2. run cmake configure and build
   cmake --preset conan-<build_type>
   cmake --build --preset conan-<build_type>
   
