#include "input.h"
#include <GLFW/glfw3.h>

void InputHandler::process_input()
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        input.w = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        input.w = false;
    }
}

void InputHandler::init(GLFWwindow *in_window)
{
    window = in_window;
}
