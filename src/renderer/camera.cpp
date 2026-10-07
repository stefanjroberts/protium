#include "camera.h"
#include <GLFW/glfw3.h>

glm::mat4 Camera::get_matrix()
{
    glm::mat4 out;
    out = perspective * view;
    return out;
}

void Camera::move(Input input)
{
    camera_yaw += 0.2f * input.mouse_delta_x;
    camera_pitch -= 0.2f * input.mouse_delta_y;

    if (camera_pitch > 89.0f)
    {
        camera_pitch = 89.0f;
    }
    if (camera_pitch < -89.0f)
    {
        camera_pitch = -89.0f;
    }

    glm::vec3 camera_direction;
    camera_direction.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    camera_direction.y = sin(glm::radians(camera_pitch));
    camera_direction.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    glm::vec3 camera_front = glm::normalize(camera_direction);

    glm::vec3 camera_right = glm::cross(camera_front, glm::vec3(0, 1, 0));

    float FB_movement = 0.02f * (input.w - input.s);
    float LR_movement = 0.02f * (input.d - input.a);

    camera_position += glm::vec3(camera_front.x * FB_movement, camera_front.y * FB_movement, camera_front.z * FB_movement);
    camera_position += glm::vec3(camera_right.x * LR_movement, camera_right.y * LR_movement, camera_right.z * LR_movement);

    view = glm::lookAt(camera_position, camera_position + camera_front, glm::vec3(0.0f, 1.0f, 0));
}

void Camera::update_perspective(float FOV, int width, int height)
{

    float aspect_ratio = (float)width / (float)height;
    perspective = glm::perspective(FOV, aspect_ratio, near_plane, far_plane);
}

glm::vec3 Camera::get_position()
{
    return camera_position;
}

Camera::Camera()
{
    near_plane = 0.1f;
    far_plane = 10.0f;
    camera_yaw = 0.0f;
    camera_pitch = 0.0f;
    camera_position = glm::vec3(0, 0, 0);
}