#pragma once
#include "../extern/glad/glad.h" //Currently fighting LLVM include style, this should be removed at some point.
#include <GLFW/glfw3.h>

struct Input
{
    bool esc = false;
    bool w;
    bool a;
    bool s;
    bool d;
    float mouse_delta_x;
    float mouse_delta_y;
};

class InputHandler
{
  private:
    GLFWwindow *window;
    float mouse_last_x = 0;
    float mouse_last_y = 0;
    double mouse_current_x;
    double mouse_current_y;

  public:
    Input input;

  public:
    InputHandler(GLFWwindow *);
    void mouse_callback(GLFWwindow *, double, double);
    void process_input();
};
