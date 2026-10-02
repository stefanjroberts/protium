#include "renderer.h"
#include "../core/file_io.h"

float vertices[] = {0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f};
unsigned int indices[] = {0,1,3, 1,2,3};

// CALLBACK FUNCTIONS
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Renderer::init(GLFWwindow *window)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PROTIUM_ERROR("Failed to initialise GLAD");
    }

    glViewport(0, 0, 1920, 1080);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    File vertex_shader_source("src/shaders/vert.glsl");
    File fragment_shader_source("src/shaders/frag.glsl");

    PROTIUM_INFO(vertex_shader_source.data);
    PROTIUM_INFO("\n\n");
    PROTIUM_INFO(fragment_shader_source.data);

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source.data, nullptr);
    glShaderSource(fragment_shader, 1, &fragment_shader_source.data, nullptr);
    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);


    int success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        PROTIUM_ERROR("Failed to Compile Vertex Shader");
        PROTIUM_ERROR(info_log);
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        PROTIUM_ERROR("Failed to Compile Fragment Shader");
        PROTIUM_ERROR(info_log);
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        PROTIUM_ERROR("Failed to Link Shader Program");
        PROTIUM_ERROR(info_log);
    }

    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}

void Renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES,6,  GL_UNSIGNED_INT, 0);
}
