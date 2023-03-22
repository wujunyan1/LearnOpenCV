#version 330 core

out vec4 FragColor;

uniform sampler2D texture2d;
uniform mat4 model;
uniform mat4 VP;

in vec2 uv;
in vec4 pos;

void main()
{
    FragColor = texture(texture2d, uv); // VP * model * pos;
}