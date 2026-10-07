#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct LightData
{
    vec3 color;
    vec3 position;
};

in vec2 tex_coord;
in vec3 normal;
in vec3 world_position;

out vec4 color;

uniform sampler2D in_texture1;
uniform LightData light_data;
uniform vec3 camera_position;
uniform Material material;

void main()
{
    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(light_data.position - world_position);

    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff * light_data.color * material.diffuse;

    float specular_strength = 0.5;
    vec3 camera_direction = normalize(camera_position - world_position);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_lum = pow(max(dot(camera_direction, reflect_direction), 0.0), material.shininess);
    vec3 specular = material.specular * specular_lum * light_data.color;

    vec3 ambient = material.ambient * light_data.color;
    color = vec4(ambient + diffuse + specular, 1.0)* texture(in_texture1, tex_coord);
} 