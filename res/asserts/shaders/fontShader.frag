#version 330 core
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D screenTexture;
uniform vec3 textColor;

void main()
{
    vec4 sampled = texture(screenTexture, TexCoords);
    //FragColor = vec4(textColor, 1.0) * sampled;
    FragColor = sampled;
}