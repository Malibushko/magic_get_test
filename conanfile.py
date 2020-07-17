from conans import ConanFile, CMake

class TestMagicGet(ConanFile):
   name = "Test"
   description = "This is the test to prove a bug"
   version = "0.1"
   license = "MIT"
   url = "https://github.com/conan-io/conan-center-index"
   settings = "os", "compiler", "build_type", "arch"
   generators = "cmake"
   requires = "magic_get/1.0", "boost/1.73.0"
   
   def source(self):
       self.run("git clone https://github.com/Malibushko/magic_get_test.git")
      
   def build(self):
      cmake = CMake(self)
      cmake.verbose = True
      self.run("cmake magic_get_test/");
      cmake.build();
