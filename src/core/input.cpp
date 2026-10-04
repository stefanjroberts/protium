#include "input.h"
#include <GLFW/glfw3.h>

void InputHandler::process_input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        input.esc = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        input.w = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        input.w = false;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        input.a = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        input.a = false;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        input.s = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
    {
        input.s = false;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        input.d = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        input.d = false;
    }
    glfwGetCursorPos(window, &mouse_current_x, &mouse_current_y);

    input.mouse_delta_x = mouse_current_x - mouse_last_x;
    input.mouse_delta_y = mouse_current_y - mouse_last_y;
    mouse_last_x = mouse_current_x;
    mouse_last_y = mouse_current_y;
}

InputHandler::InputHandler(GLFWwindow *in_window)
{
    window = in_window;
}
