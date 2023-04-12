#version 330 core
in vec2 uv;

out vec4 FragColor;

uniform sampler2D screenTexture;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(textColor.rgb, texture(screenTexture, uv).r);
    //FragColor = vec4(textColor, 1.0);
    //FragColor = texture(screenTexture, uv);
    FragColor = sampled;
}