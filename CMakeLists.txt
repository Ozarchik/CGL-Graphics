cmake_minimum_required(VERSION 3.10)
project(CGL-Graphics)

find_package(CGLHelper)


include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/examples)
include_directories(C:/libs/glfw/install/include)
include_directories(C:/libs/glad/include)
include_directories(C:/libs/glm/install/include)
include_directories(C:/libs/assimp/deploy/include)

set(GLFW_LIB C:/libs/glfw/install/bin/glfw3.dll)
set(GLM_LIB C:/libs/glm/install/bin/libglm.dll)
set(ASSIMP_LIB C:/libs/assimp/deploy/bin/libassimp-5.dll)


add_executable(${PROJECT_NAME}
    examples/lightscene.h examples/lightscene.cpp
    src/model.h src/model.cpp
    src/textureloader.h src/textureloader.cpp
    src/meshbuffer.h src/meshbuffer.cpp
    src/object.h src/object.cpp
    src/event.h src/event.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW_LIB}
    ${GLM_LIB}
    ${ASSIMP_LIB}
)

file(GLOB sources
    "src/*.cpp"
    "examples/*.cpp"
    "C:/libs/glad/src/glad.c"
)

file(GLOB headers
    "src/*.h"
    "examples/*.h"
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
    DIRECTORY
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_SOURCE_DIR}/textures
    ${CMAKE_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_BINARY_DIR}
)

install (
    FILES
    ${GLFW_LIB} ${ASSIMP_LIB}
    DESTINATION ${CMAKE_BINARY_DIR}
)

# install(
#     DIRECTORY )
# )

# add_custom_command (
#     TARGET ${PROJECT_NAME}
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND}
#     -E copy_directory_if_different
#     "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
#     "${CMAKE_BINARY_DIR}>/shaders"
# )

# add_custom_command (
#     TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     $<TARGET_RUNTIME
# )
