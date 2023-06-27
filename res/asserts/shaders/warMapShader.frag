#version 330 core
in vec2 TexCoord;
in float ap;

out vec4 FragColor;
uniform sampler2D mapTexture;

void main()
{
    //FragColor = vertexColor;
    vec4 texColor = texture(mapTexture, TexCoord);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor; // vec4(TexCoord, 1.0, 1.0); // texColor;
    FragColor.a = ap;
}