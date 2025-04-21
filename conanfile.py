from conan import ConanFile

class XrbdsRecipe(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("glm/1.0.1")
