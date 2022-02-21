#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 ambientColor;
uniform sampler2D ourTexture;

void main()
{
    //FragColor = vertexColor;
    FragColor = vec4(1.0,1.0,1.0, 1.0);
}