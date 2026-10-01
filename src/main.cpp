#include "logger.cpp"
#include "opengl.cpp"
#include <GLFW/glfw3.h>

int main() {

  glfwInit();
  // NOTE: Currently only supporting opengl for renderer backend
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(1920, 1080, "Protium", nullptr, nullptr);

  if (window == nullptr) {
    logger.error("Failed to create GLFW window");
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);

  OGL_backend *renderer = new OGL_backend;
  renderer->init();

  return 0;
}
