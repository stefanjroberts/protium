#pragma once
#include "extern/glad/glad.h"
#include "logger.cpp"
#include <GLFW/glfw3.h>

class OGL_backend {

public:
  void init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      logger.error("Failed to initialise GLAD");
    }
  }
};
