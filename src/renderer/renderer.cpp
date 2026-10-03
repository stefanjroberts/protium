#include "renderer.h"
#include "../core/file_io.h"
#include "math.h"

float vertices1[] = {0.5, -0.75, 0.0, 0.5, -0.25, 0.0, -0.5, -0.5, 0.0};

unsigned int indices1[] = {0, 1, 2};

float vertices2[] = {-0.5, 0.25, 0.0, 0.5, 0.5, 0.0, -0.5, 0.75, 0.0};

unsigned int indices2[] = {0, 1, 2};

// CALLBACK FUNCTIONS
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
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

void Renderer::init(GLFWwindow *window)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PROTIUM_ERROR("Failed to initialise GLAD");
    }

    glViewport(0, 0, 1300, 1350);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);

    shader_program = new ShaderProgram("src/shaders/vert.glsl", "src/shaders/frag.glsl");
    shader_program2 = new ShaderProgram("src/shaders/vert.glsl", "src/shaders/frag2.glsl");

    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    counter = 0.0f;

    color_uniform = glGetUniformLocation(shader_program->ID, "uniform_color");
    color_uniform2 = glGetUniformLocation(shader_program2->ID, "uniform_color");
}

void Renderer::render()
{
    counter += 0.1f;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program->ID);
    glUniform3f(color_uniform, 0.5f + 0.5 * sin(counter), 0.0f, 0.0f);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glUseProgram(shader_program2->ID);

    glUniform3f(color_uniform2, 0.0f, 0.5f + 0.5 * sin(counter), 0.0f);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
