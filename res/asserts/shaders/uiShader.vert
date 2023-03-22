#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform vec3 color;
uniform mat4 model;
uniform mat4 VP;

out vec2 uv;
out vec4 pos;

void main()
{
    uv = aTexCoords;
    //pos = VP * model * vec4(aPos, 1.0);
    gl_Position = VP * model * vec4(aPos.xy, 0.0, 1.0); // VP * model * 
}