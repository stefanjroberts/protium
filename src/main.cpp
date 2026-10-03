#include "core/input.cpp"
#include "core/logger.cpp"
#include "core/file_io.cpp"
#include "renderer/renderer.cpp"

int main()
{
    glfwInit();
    // NOTE: Currently only supporting opengl for renderer backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Protium", nullptr, nullptr);

    if (window == nullptr)
    {
        PROTIUM_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    Renderer *renderer = new Renderer(window);
    InputHandler *input_handler = new InputHandler;
    input_handler->init(window);

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
        if (input_handler->input.w)
        {
            PROTIUM_INFO("W");
        }

        renderer->render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
