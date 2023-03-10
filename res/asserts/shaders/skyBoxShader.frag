#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;

in vec3 TexCoords; // ����3D��������ķ�������
uniform samplerCube cubemap; // ��������ͼ�����������

void main()
{
    FragColor = texture(cubemap, TexCoords);
}