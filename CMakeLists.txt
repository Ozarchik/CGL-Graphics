cmake_minimum_required(VERSION 3.25)
project(CGL-Graphics)

find_package(assimp REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

file(GLOB sources
    "cgl/*.cpp"
    "cgl/mesh/2D/*.cpp"
    "cgl/mesh/3D/*.cpp"
    "cgl/mesh/common/*.cpp"
    "cgl/event/*.cpp"
    "cgl/model/*.cpp"
    "cgl/texture/*.cpp"
    "examples/*.cpp"
    # "C:/libs/glad/src/glad.c"
)

file(GLOB headers
    "include/cgl/*.h"
    "include/cgl/mesh/2D/*.h"
    "include/cgl/mesh/3D/*.h"
    "include/cgl/mesh/common/*.h"
    "include/cgl/event/*.h"
    "include/cgl/model/*.h"
    "include/cgl/texture/*.h"
    "examples/*.h"
)

file(GLOB shaders
    "shaders/*"
)

add_executable(cglg)

target_sources(cglg PRIVATE
    ${sources}
    ${headers}
    ${shaders}
)

target_link_libraries(cglg PRIVATE
    assimp::assimp
    glm::glm
    glad::glad
    glfw
)

target_include_directories(cglg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/examples
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/meshes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/event
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/model
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/texture
    ${CMAKE_CURRENT_SOURCE_DIR}
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
