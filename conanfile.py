import os

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.files import copy

class CGLGraphicsRecipe(ConanFile):
    generators = "CMakeDeps", "CMakeToolchain"
    settings = "os", "arch", "build_type", "compiler"


    def generate(self):
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))

    def requirements(self):
        self.requires("glad/0.1.36")
        self.requires("glfw/3.4")
        self.requires("glm/1.0.1")
        self.requires("assimp/5.4.3")
        self.requires("cpptrace/0.7.5")
        self.requires("imgui/1.92.0-docking")

    def build(self):
        cmake = CMake(self)
        cmake.build()

    def layout(self):
        cmake_layout(self)
