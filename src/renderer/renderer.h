#pragma once
#include "../core/logger.h"
#include "../extern/glad/glad.h"
#include <GLFW/glfw3.h>

struct Vertex
{
    float position[3];
    float texture_coordinates[2];
};

class ShaderProgram
{
  public:
    unsigned int ID;
    ShaderProgram(const char *vertex_file, const char *fragment_file);
    void use();
};

class Texture
{
  private:
    unsigned int ID;
    int width;
    int height;
    int channel_count;

  public:
    Texture(const char *location);
    void bind();
};

class Renderer
{
  private:
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    ShaderProgram *shader_program;
    Texture *texture;

  public:
    void init(GLFWwindow *window);
    void render();
};
