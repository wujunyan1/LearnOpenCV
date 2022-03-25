#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform vec3 color;
uniform mat4 model;
uniform mat4 VP;
uniform mat4 view;
uniform mat4 proj;

out vec2 uv;

void main()
{
    uv = aTexCoords;
    gl_Position = VP * model * vec4(aPos, 1.0);
}