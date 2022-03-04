#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 color;
uniform mat4 model;

void main()
{
    gl_Position = vec4(aPos.x + 0.5f, aPos.y, aPos.z, 1.0);
}