#pragma once
#include "../core/logger.h"
#include "../extern/glad/glad.h"
#include <GLFW/glfw3.h>

class Renderer
{
  private:
    unsigned int VBO;
  public:
    void init(GLFWwindow *);
    void render();
};
