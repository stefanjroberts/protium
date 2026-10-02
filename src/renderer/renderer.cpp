#include "renderer.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f    
};

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
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Renderer::render()
{
    glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
