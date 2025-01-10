cmake_minimum_required(VERSION 3.5)
project(MyProject)

# include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(C:/libs/glfw-3.4/install/include)
include_directories(C:/libs/glad/include)
include_directories(C:/libs/glm/install/include)
include_directories(C:/libs/assimp/deploy/include)

file(GLOB sources
    "src/*.cpp"
    "C:/libs/glad/src/glad.c"
)

file(GLOB headers
    "src/*.h"
)

set(GLFW_LIB C:/libs/glfw-3.4/install/bin/glfw3.dll)
set(GLM_LIB C:/libs/glm/install/bin/libglm.dll)
set(ASSIMP_LIB C:/libs/assimp/deploy/bin/libassimp-5.dll)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW_LIB}
    ${GLM_LIB}
    ${ASSIMP_LIB}
)

