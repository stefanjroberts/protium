#version 330 core
in vec2 tex_coord;
in vec3 normal;
in vec3 world_position;

out vec4 color;

uniform sampler2D in_texture1;
uniform vec3 light;
uniform vec3 light_position;
uniform vec3 camera_position;

void main()
{
    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(light_position - world_position);

    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff * light;

    float specular_strength = 0.5;
    vec3 camera_direction = normalize(camera_position - world_position);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_lum = pow(max(dot(camera_direction, reflect_direction), 0.0), 32);
    vec3 specular = specular_strength * specular_lum * light;

    vec3 ambient = 0.1 * light;
    color = vec4(ambient + diffuse + specular, 1.0)* texture(in_texture1, tex_coord);
} 