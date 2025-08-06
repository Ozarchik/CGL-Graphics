cmake_minimum_required(VERSION 3.25)
project(CGL-Graphics)
set(CMAKE_CXX_STANDARD 20)
find_package(assimp REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)

file(GLOB sources
    "cgl/*.cpp"
    "cgl/mesh/2D/*.cpp"
    "cgl/mesh/3D/*.cpp"
    "cgl/mesh/common/*.cpp"
    "cgl/event/*.cpp"
    "cgl/ui/*.cpp"
    "cgl/model/*.cpp"
    "cgl/texture/*.cpp"
    "cgl/tools/backtrace/*.cpp"
    # "examples/*.cpp"
    # "C:/libs/glad/src/glad.c"
)

file(GLOB headers
    "include/cgl/*.h"
    "include/cgl/mesh/2D/*.h"
    "include/cgl/mesh/3D/*.h"
    "include/cgl/mesh/common/*.h"
    "include/cgl/event/*.h"
    "include/cgl/ui/*.h"
    "include/cgl/model/*.h"
    "include/cgl/texture/*.h"
    "include/cgl/tools/backtrace/*.h"
    # "examples/*.h"
)

file(GLOB shaders
    "shaders/*"
)

add_executable(cglg)
target_compile_definitions(cglg PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_sources(cglg PRIVATE
    ${sources}
    ${headers}
    ${shaders}
    bindings/imgui_impl_glfw.cpp
    bindings/imgui_impl_glfw.h
    bindings/imgui_impl_opengl3.cpp
    bindings/imgui_impl_opengl3.h
    bindings/imgui_impl_opengl3_loader.h
    # assets/simple-shader.vs
    # assets/simple-shader.fs
)

target_link_libraries(cglg PRIVATE
    imgui::imgui
    assimp::assimp
    glm::glm
    glad::glad
    glfw
)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    find_package(cpptrace REQUIRED)
    target_link_libraries(cglg PRIVATE
        cpptrace::cpptrace
    )

    add_compile_definitions(USE_BACKTRACE)
endif()

target_include_directories(cglg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/examples
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/meshes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/event
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/model
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/texture
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cgl/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/include/backtrace
    ${CMAKE_CURRENT_SOURCE_DIR}/bindings
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