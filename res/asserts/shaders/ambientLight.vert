#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aColor;
out vec4 vertexColor;
uniform vec4 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 ambientColor;

out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
    TexCoord = aTexCoord; //aTexCoord;
}