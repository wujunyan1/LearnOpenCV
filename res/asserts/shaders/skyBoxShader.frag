#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;

in vec3 TexCoords; // 代表3D纹理坐标的方向向量
uniform samplerCube cubemap; // 立方体贴图的纹理采样器

void main()
{
    FragColor = texture(cubemap, TexCoords);
}