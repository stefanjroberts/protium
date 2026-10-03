#version 330 core
out vec4 color;

uniform vec3 uniform_color;

void main()
{
    color = vec4(0.0f, 1.0f, 0.0f, 1.0f) - vec4(uniform_color, 0.0f);
} 