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
    "cgl/core/*.cpp"
    "cgl/core/command/*.cpp"
    "cgl/core/event/*.cpp"
    "cgl/graphics/*.cpp"
    "cgl/graphics/mesh/2D/*.cpp"
    "cgl/graphics/mesh/3D/*.cpp"
    "cgl/graphics/mesh/common/*.cpp"
    "cgl/graphics/model/*.cpp"
    "cgl/graphics/texture/*.cpp"
    "cgl/graphics/material/*.cpp"
    "cgl/graphics/scene/*.cpp"
    "cgl/graphics/vertex/*.cpp"
    "cgl/managers/*.cpp"
    "cgl/ui/*.cpp"
    "cgl/physics/*.cpp"
    "cgl/tools/backtrace/*.cpp"
    # "examples/*.cpp"
)

file(GLOB headers
    "include/cgl/*.h"
    "include/cgl/core/*.h"
    "include/cgl/core/command/*.h"
    "include/cgl/core/event/*.h"
    "include/cgl/graphics/*.h"
    "include/cgl/graphics/mesh/2D/*.h"
    "include/cgl/graphics/mesh/3D/*.h"
    "include/cgl/graphics/mesh/common/*.h"
    "include/cgl/graphics/model/*.h"
    "include/cgl/graphics/texture/*.h"
    "include/cgl/graphics/material/*.h"
    "include/cgl/graphics/scene/*.h"
    "include/cgl/graphics/vertex/*.h"
    "include/cgl/tools/backtrace/*.h"
    "include/cgl/managers/*.h"
    "include/cgl/ui/*.h"
    "include/cgl/physics/*.h"
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
    thirdparty/imgui/bindings/imgui_impl_glfw.cpp
    thirdparty/imgui/bindings/imgui_impl_glfw.h
    thirdparty/imgui/bindings/imgui_impl_opengl3.cpp
    thirdparty/imgui/bindings/imgui_impl_opengl3.h
    thirdparty/imgui/bindings/imgui_impl_opengl3_loader.h
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
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty
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


