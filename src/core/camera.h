#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "input.h"

class Camera
{
    private:
        glm::mat4 view;
        glm::mat4 perspective;
        float far_plane;
        float near_plane;
        float camera_yaw;
        float camera_pitch;
        glm::vec3 camera_position;
    
    public:
        Camera();
        glm::mat4 get_matrix();
        void update_perspective(float FOV, int width, int height);
        void move(Input input);
};