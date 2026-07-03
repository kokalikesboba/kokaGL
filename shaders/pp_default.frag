#version 330 core

in vec2 vertUV;
out vec4 FragColor;

uniform sampler2D screenTexture;

void main()
{
    FragColor = texture(screenTexture, vertUV);
}