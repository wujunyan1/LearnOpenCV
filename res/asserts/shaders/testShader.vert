#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 color;
uniform mat4 model;
uniform mat4 VP;
uniform mat4 view;
uniform mat4 pres;

out vec4 test;

void main()
{
    test = pres * view * model * vec4(aPos, 1.0);
    gl_Position = view *  model * vec4(aPos, 1.0);
}