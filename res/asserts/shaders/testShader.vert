#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 VP;
uniform mat4 view;
uniform mat4 proj;

out vec2 uv;
out vec4 worldPos;

void main()
{
    uv = aTexCoords;
    worldPos = model * vec4(aPos, 1.0);
    gl_Position = VP * worldPos;
}