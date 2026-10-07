#version 330 core
in vec2 tex_coord;
out vec4 color;

uniform sampler2D in_texture1;
uniform vec3 light_color;

void main()
{
    color = vec4(light_color, 1.0f);
} 