#pragma once
#include "../core/logger.h"
#include "../extern/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>

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
    Texture(const char *location, unsigned int type);
    void bind(unsigned int texture_index);
};

class Renderer
{
  private:
    float counter;

    int screen_width;
    int screen_height;
    float aspect_ratio;

    float FOV_radians = 0.8; // NOTE: This is not the full FOV, it is half the FOV, i.e. the angle between the center of the screen and the edge.
    float near_face = 0.1f;
    float far_face = 10.0f;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    ShaderProgram *shader_program;
    Texture *texture;
    Texture *texture2;

  public:
    Renderer(GLFWwindow *window);
    void init_transformations();
    void render();
};
