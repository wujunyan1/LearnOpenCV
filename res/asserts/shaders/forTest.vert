#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec3 aNormal;

out vec4 vertexColor;
uniform vec4 ourColor;

uniform mat4 model;
uniform mat4 modelInverse;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

out vec2 TexCoord;
out vec3 Normal;
out vec3 WorldPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
    TexCoord = aTexCoord; //aTexCoord;

    WorldPos = vec3(model * vec4(aPos, 1.0));

    Normal = mat3(transpose(modelInverse)) * aNormal; // vec3(model * vec4(aNormal, 0.0));
}