#version 330 core

in vec2 vertUV;

uniform sampler2D screenTexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(screenTexture, vertUV);
}