#version 330 core
in vec2 tex_coord;
out vec4 color;

uniform sampler2D in_texture1;

void main()
{
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
} 