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
    float normal[3];
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

class Model
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    glm::mat4 model_matrix;
    Texture *tex;
    size_t vertex_count;
    size_t index_count;

    Vertex *vertices;
    int *indices;

  public:
    Model(Vertex *vertices, size_t in_vertex_count, unsigned int *indices, size_t in_index_count, Texture *in_texture);
    void draw(Camera *camera, int PVM_unifrom);
    void update_matrix(glm::mat4 matrix);
};

class RenderModule
{
  public:
    ShaderProgram *shader_program;
    Model **models;
    int max_model_count;
    int model_count;

  public:
    RenderModule(const char *vertex_file_path, const char *fragment_file_path, int model_count);
    void addmodel(Model *model);
    void render(Camera *camera);
    void set_uniform3f(const char *name, glm::vec3 value);
    void set_uniform4m(const char* name, glm::mat4 value);
};

class Renderer
{
  private:
    float counter;
    glm::vec3 light_position = glm::vec3(1.2f, 2.0f, 2.0f);

    RenderModule *light_render_module;
    RenderModule *box_render_module;
    Model *light_model;
    Model *box_model;

    Texture *texture;

  public:
    Renderer(GLFWwindow *window);
    void render(Camera *camera);
};
