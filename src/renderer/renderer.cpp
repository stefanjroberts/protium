#include "renderer.h"
#include "../core/file_io.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "../extern/stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

Vertex vertices1[] = {{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
                      {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},   {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
                      {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},  {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},

                      {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},   {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
                      {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},     {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
                      {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},

                      {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},   {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
                      {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}, {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
                      {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},  {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},

                      {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},     {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
                      {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},   {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
                      {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},    {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

                      {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}, {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
                      {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},   {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
                      {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},  {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},

                      {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},   {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
                      {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},     {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                      {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}};

unsigned int indices1[36] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
                             18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

ShaderProgram::ShaderProgram(const char *vertex_file_path, const char *fragment_file_path)
{
    ID = glCreateProgram();
    File vertex_shader_source(vertex_file_path);
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source.data, nullptr);
    glCompileShader(vertex_shader);
    int success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        PROTIUM_ERROR("Failed to Compile Vertex Shader");
        PROTIUM_ERROR(info_log);
    }
    glAttachShader(ID, vertex_shader);

    File fragment_shader_source(fragment_file_path);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source.data, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        PROTIUM_ERROR("Failed to Compile Fragment Shader");
        PROTIUM_ERROR(info_log);
    }
    glAttachShader(ID, fragment_shader);

    glLinkProgram(ID);
    glGetProgramiv(ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(ID, 512, nullptr, info_log);
        PROTIUM_ERROR("Failed to Link Shader Program");
        PROTIUM_ERROR(info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void ShaderProgram::use()
{
    glUseProgram(ID);
}

Texture::Texture(const char *location, unsigned int type)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    unsigned char *data = stbi_load(location, &width, &height, &channel_count, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::bind(unsigned int texture_index)
{
    glActiveTexture(texture_index);
    glBindTexture(GL_TEXTURE_2D, ID);
}

Model::Model(Vertex *vertices, size_t in_vertex_count, unsigned int *indices, size_t in_index_count, Texture *in_texture)
{
    vertex_count = in_vertex_count;
    index_count = in_index_count;
    tex = in_texture;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * in_vertex_count, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * in_index_count, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    model_matrix = glm::mat4(1.0f);
}

void Model::draw(Camera *camera, int PVM_uniform, ShaderProgram *shader)
{

    glm::mat4 PVM = camera->get_matrix() * model_matrix;

    if (material.in_use)
    {
        glUniform3f(glGetUniformLocation(shader->ID, "material.ambient"), material.ambient.x, material.ambient.y, material.ambient.z);
        glUniform3f(glGetUniformLocation(shader->ID, "material.diffuse"), material.diffuse.x, material.diffuse.y, material.diffuse.z);
        glUniform3f(glGetUniformLocation(shader->ID, "material.specular"), material.specular.x, material.specular.y, material.specular.z);
        glUniform1f(glGetUniformLocation(shader->ID, "material.shininess"), material.shininess);
    }
    else
    {
        glUniform3f(glGetUniformLocation(shader->ID, "material.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(shader->ID, "material.diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(shader->ID, "material.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(shader->ID, "material.shininess"), 32.0f);
    }

    glUniformMatrix4fv(PVM_uniform, 1, GL_FALSE, (float *)&PVM);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}

void Model::update_matrix(glm::mat4 matrix)
{
    model_matrix = matrix;
}

void Model::set_material(Material in_material)
{
    material = in_material;
    material.in_use = true;
}

RenderModule::RenderModule(const char *vertex_file_path, const char *fragment_file_path, int in_max_model_count)
{
    shader_program = new ShaderProgram(vertex_file_path, fragment_file_path);
    models = new Model *[in_max_model_count];
    max_model_count = in_max_model_count;
    model_count = 0;
}

void RenderModule::addmodel(Model *model)
{
    if (model_count == max_model_count)
    {
        PROTIUM_ERROR("Tried to add too many models to Render Module");
    }
    else
    {
        models[model_count] = model;
        model_count += 1;
    }
}

void RenderModule::render(Camera *camera)
{
    shader_program->use();
    int PVM_uniform = glGetUniformLocation(shader_program->ID, "PVM_matrix");
    for (int i = 0; i < model_count; i++)
    {
        models[i]->draw(camera, PVM_uniform, this->shader_program);
    }
}

void RenderModule::set_uniform3f(const char *name, glm::vec3 value)
{
    glUseProgram(shader_program->ID);
    int programID = glGetUniformLocation(shader_program->ID, name);
    glUniform3f(programID, (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z);
}

void RenderModule::set_uniform4m(const char *name, glm::mat4 value)
{
    glUseProgram(shader_program->ID);
    int programID = glGetUniformLocation(shader_program->ID, name);
    glUniformMatrix4fv(programID, 1, GL_FALSE, (float *)&value);
}

Renderer::Renderer(GLFWwindow *window)
{
    stbi_set_flip_vertically_on_load(true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PROTIUM_ERROR("Failed to initialise GLAD");
    }

    int screen_width;
    int screen_height;
    glfwGetWindowSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

    texture = new Texture("assets/container.jpg", GL_RGB);

    glEnable(GL_DEPTH_TEST);

    Vertex *vertex_data = (Vertex *)vertices1;

    glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 0.0f);

    light_model = new Model(vertex_data, 36, indices1, 36, texture);
    light_render_module = new RenderModule("shaders/vert.glsl", "shaders/frag_light.glsl", 1);
    light_render_module->addmodel(light_model);
    light_render_module->set_uniform3f("light_color", light_color);

    Material material;
    material.ambient = {0.1, 0.1, 0.1};
    material.diffuse = {0.6, 0.6, 0.6};
    material.specular = {0.8, 0.8, 0.8};
    material.shininess = 128.0f;

    box_model = new Model(vertex_data, 36, indices1, 36, texture);
    box_model->set_material(material);
    box_render_module = new RenderModule("shaders/vert.glsl", "shaders/frag.glsl", 1);
    box_render_module->addmodel(box_model);
    box_render_module->set_uniform3f("light_data.color", light_color);
}

void Renderer::render(Camera *camera)
{
    counter += 0.01f;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    light_position.y = 2.0f * sin(counter);
    light_position.z = 2.0f * cos(counter);

    glm::mat4 light_matrix = glm::scale(glm::translate(glm::mat4(1.0f), light_position), glm::vec3(0.2f));
    light_model->update_matrix(light_matrix);
    glm::mat4 box_matrix =
        glm::translate(glm::rotate(glm::mat4(1.0f), counter * glm::radians(-50.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(0, 0, -1));
    box_model->update_matrix(box_matrix);

    box_render_module->set_uniform3f("light_data.position", light_position);
    box_render_module->set_uniform4m("model_matrix", box_matrix);
    box_render_module->set_uniform3f("camera_position", camera->get_position());

    glm::vec3 light_color = glm::vec3(cos(counter), 1.0f, sin(counter));
    light_render_module->set_uniform3f("light_color", light_color);
    box_render_module->set_uniform3f("light_data.color", light_color);

    light_render_module->render(camera);
    box_render_module->render(camera);
}
