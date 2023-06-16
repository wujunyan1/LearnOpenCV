#version 330 core
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D diffuse;

void main()
{
    //FragColor = vertexColor;
    vec4 texColor = texture(diffuse, TexCoord);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}