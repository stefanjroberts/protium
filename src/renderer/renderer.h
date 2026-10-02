#pragma once
#include "../core/logger.h"
#include "../extern/glad/glad.h"
#include <GLFW/glfw3.h>

class Renderer
{
  private:
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shader_program;

  public:
    void init(GLFWwindow *);
    void render();
};
