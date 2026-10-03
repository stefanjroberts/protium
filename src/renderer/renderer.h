#pragma once
#include "../core/logger.h"
#include "../extern/glad/glad.h"
#include <GLFW/glfw3.h>

class ShaderProgram
{
  public:
    unsigned int ID;
    ShaderProgram(const char *vertex_file, const char *fragment_file);
    void use();
};

class Renderer
{
  private:
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    ShaderProgram* shader_program;

    int color_uniform;

    unsigned int EBO2;
    unsigned int VBO2;
    unsigned int VAO2;
    ShaderProgram* shader_program2;

    int color_uniform2;

    float counter;

  public:
    void init(GLFWwindow *window);
    void render();
};
