#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform vec2 imageUV;
uniform mat4 model;
uniform mat4 VP;


out vec2 TexCoords;

void main()
{
    gl_Position = VP * model * vec4((vec2(aPos.x, aPos.y)), 0.0, 1.0);
    //gl_Position = vec4(vec2(aPos.x, aPos.y), 0.0, 1.0);
    TexCoords = imageUV * aTexCoords;
}