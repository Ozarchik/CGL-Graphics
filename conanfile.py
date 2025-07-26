from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class CGLGraphicsRecipe(ConanFile):
    generators = "CMakeDeps", "CMakeToolchain"
    settings = "os", "arch", "build_type", "compiler"

    def requirements(self):
        self.requires("glad/0.1.36")
        self.requires("glfw/3.4")
        self.requires("glm/1.0.1")
        self.requires("assimp/5.4.3")

    def build(self):
        cmake = CMake(self)
        cmake.build()

    def layout(self):
        cmake_layout(self)
