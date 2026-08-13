#version 410 core

in vec3 vertPosition;
in vec3 vertNormal;
in vec2 vertUV;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}