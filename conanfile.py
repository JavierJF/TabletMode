from conans import ConanFile, CMake, tools
import os

class TabletModeConan(ConanFile):
    name = "TabletMode"
    version = "0.1"
    license = "Raising The Floor"
    url = "https://github.com/JavierJF/TabletMode"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "tests": [True, False]}
    generators = "cmake"
    requires = (
        "UErrno/0.1@javjarfer/testing",
    )
    default_options = (
        "shared=False",
        "tests=False",
    )

    def source(self):
        self.run("git clone https://github.com/JavierJF/TabletMode")
        self.run("cd TabletMode && git checkout develop")

    def build(self):
        cmake = CMake(self, parallel=True)
        cmake.configure(source_folder="TabletMode")
        cmake.build(target="install")

    def imports(self):
       self.copy("*.dll", "bin")

