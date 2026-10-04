#include "core/file_io.cpp"
#include "core/input.cpp"
#include "core/logger.cpp"
#include "core/camera.cpp"
#include "renderer/renderer.cpp"
#include <GLFW/glfw3.h>

bool screen_size_changed = true;
int screen_size[2] = {100, 100}; // TODO: Remove Globals

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    screen_size_changed = true;
    screen_size[0] = width;
    screen_size[1] = height;
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    // NOTE: Currently only supporting opengl for renderer backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Protium", nullptr, nullptr);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (window == nullptr)
    {
        PROTIUM_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Renderer *renderer = new Renderer(window);
    InputHandler *input_handler = new InputHandler(window);
    Camera *camera = new Camera;

    PROTIUM_INFO("Entering main Loop");

    bool running = true;

    while (running == true)
    {

        glfwPollEvents();
        if (glfwWindowShouldClose(window))
        {
            running = false;
        }
        input_handler->process_input();
        if (input_handler->input.esc == true)
        {
            glfwSetWindowShouldClose(window, true);
        }
        if (screen_size_changed)
        {
            camera->update_perspective(1.0, screen_size[0], screen_size[1]);
            screen_size_changed = false;
        }
        camera->move(input_handler->input);
        renderer->render(camera);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
