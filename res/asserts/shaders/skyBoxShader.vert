#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 view;
uniform mat4 proj;

out vec3 TexCoords;
out vec4 worldPos;

void main()
{
    TexCoords = aPos;
    vec4 pos = proj * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}