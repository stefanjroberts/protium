#include "renderer.h"
#include "../core/file_io.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "../extern/stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

float vertices1[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

                     -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

                     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
                     0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
                     0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                     -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

unsigned int indices1[36];

int screen_size[2] = {100, 100};

// CALLBACK FUNCTIONS
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    screen_size[0] = width;
    screen_size[1] = height;
    glViewport(0, 0, width, height);
}

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

Renderer::Renderer(GLFWwindow *window)
{
    for (int i = 0; i < 36; i++)
    {
        indices1[i] = i;
    }

    stbi_set_flip_vertically_on_load(true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PROTIUM_ERROR("Failed to initialise GLAD");
    }

    glfwGetWindowSize(window, &screen_width, &screen_height);
    aspect_ratio = ((float)screen_width) / ((float)screen_height);

    glViewport(0, 0, screen_width, screen_height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    shader_program = new ShaderProgram("shaders/vert.glsl", "shaders/frag.glsl");

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    texture = new Texture("assets/container.jpg", GL_RGB);

    shader_program->use();

    glUniform1i(glGetUniformLocation(shader_program->ID, "in_texture1"), 0);

    init_transformations();

    counter = 0.0f;

    glEnable(GL_DEPTH_TEST);
}

void Renderer::init_transformations()
{
    model = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    camera_yaw = 0;
    camera_pitch = 0;
    camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
    projection = glm::perspective(1.0f, aspect_ratio, 0.1f, 10.0f);
}

void Renderer::render(Input input)
{
    counter += 0.02f;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    aspect_ratio = (float) screen_size[0]/ (float) screen_size[1];

    projection = glm::perspective(1.0f, aspect_ratio, 0.1f, 10.0f);
    model = glm::rotate(model, 0.01f * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 4.0f));

    camera_yaw += 0.2f * input.mouse_delta_x;
    camera_pitch -= 0.2f * input.mouse_delta_y;

    if (camera_pitch > 89.0f)
    {
        camera_pitch = 89.0f;
    }
    if (camera_pitch < -89.0f)
    {
        camera_pitch = -89.0f;
    }

    glm::vec3 camera_direction;
    camera_direction.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    camera_direction.y = sin(glm::radians(camera_pitch));
    camera_direction.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    glm::vec3 camera_front = glm::normalize(camera_direction);

    glm::vec3 camera_right = glm::cross(camera_front, glm::vec3(0, 1, 0));

    float FB_movement = 0.02f * (input.w - input.s);
    float LR_movement = 0.02f * (input.d - input.a);

    camera_position += glm::vec3(camera_front.x * FB_movement, camera_front.y * FB_movement, camera_front.z * FB_movement);
    camera_position += glm::vec3(camera_right.x * LR_movement, camera_right.y * LR_movement, camera_right.z * LR_movement);

    view = glm::lookAt(camera_position, camera_position + camera_front, glm::vec3(0.0f, 1.0f, 0));

    glm::mat4 camera = projection * view * model;

    int camera_uniform = glGetUniformLocation(shader_program->ID, "camera");
    glUniformMatrix4fv(camera_uniform, 1, GL_FALSE, (float *)&camera);

    shader_program->use();
    texture->bind(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
