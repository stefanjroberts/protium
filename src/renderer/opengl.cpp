#include "opengl.h"

void Renderer::init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PROTIUM_ERROR("Failed to initialise GLAD");
    }
}
