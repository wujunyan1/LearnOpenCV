#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;

void main()
{
    FragColor = model[1];
}