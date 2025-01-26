cmake_minimum_required(VERSION 3.10)
project(CGL-Graphics)

find_package(CGLHelper)


include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(C:/libs/glfw/install/include)
include_directories(C:/libs/glad/include)
include_directories(C:/libs/glm/install/include)
include_directories(C:/libs/assimp/deploy/include)

set(GLFW_LIB C:/libs/glfw/install/bin/glfw3.dll)
set(GLM_LIB C:/libs/glm/install/bin/libglm.dll)
set(ASSIMP_LIB C:/libs/assimp/deploy/bin/libassimp-5.dll)


add_executable(${PROJECT_NAME}
    src/inputcontroller.h src/inputcontroller.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW_LIB}
    ${GLM_LIB}
    ${ASSIMP_LIB}
)

file(GLOB sources
    "src/*.cpp"
    "C:/libs/glad/src/glad.c"
)

file(GLOB headers
    "src/*.h"
)

file(GLOB shaders
    "shaders/*"
)

target_sources(${PROJECT_NAME} PRIVATE
    ${sources}
    ${headers}
    ${shaders}
)


install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/shaders
    DESTINATION ${CMAKE_BINARY_DIR}
)


# add_custom_command (
#     TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     $<TARGET_RUNTIME
# )
