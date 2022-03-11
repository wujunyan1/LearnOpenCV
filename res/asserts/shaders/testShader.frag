#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;

in vec4 test;

void main()
{
    vec4 v = test * 0.5 + 0.5;
    FragColor = vec4(v.xyz, 1.0f);
}