#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;

uniform sampler2D texture_diffuse1;
in vec2 uv;

void main()
{
    FragColor = texture(texture_diffuse1, uv);
}