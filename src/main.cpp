#include "core/logger.h"
#include "core/window.h"
#include "renderer/opengl.h"
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();
    // NOTE: Currently only supporting opengl for renderer backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Protium", nullptr, nullptr);

    if (window == nullptr)
    {
        PROTIUM_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    Renderer *renderer = new Renderer;
    renderer->init(window);

    PROTIUM_INFO("Entering main Loop");

    bool running = true;

    while (running == true)
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (glfwWindowShouldClose(window))
        {
            running = false;
        }
    }

    glfwTerminate();
    return 0;
}
