#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texture_coordinates;
layout (location = 2) in vec3 surface_normal;

out vec2 tex_coord;
out vec3 normal;
out vec3 world_position;

uniform mat4x4 model_matrix;
uniform mat4x4 PVM_matrix;

void main()
{
    gl_Position = PVM_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
    world_position = vec3(model_matrix*vec4(pos, 1.0));
    tex_coord = texture_coordinates;
    normal = mat3(transpose(inverse(model_matrix)))*surface_normal; // TODO: Move this out of shader code 
}