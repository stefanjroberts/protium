#pragma once
#include "../extern/glad/glad.h" //Currently fighting LLVM include style, this should be removed at some point.
#include <GLFW/glfw3.h>

struct Input
{
    bool w;
    bool a;
    bool s;
    bool d;
};

class InputHandler
{
  private:
    GLFWwindow *window;

  public:
    Input input;

  public:
    void init(GLFWwindow *);
    void process_input();
};
