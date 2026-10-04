#pragma once
#include "../core/camera.h"
#include "../core/input.h"
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

    glm::vec3 camera_position;
    float camera_yaw;
    float camera_pitch;

    float movement_speed = 0.01f;

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
    void render(Camera* camera);
};
