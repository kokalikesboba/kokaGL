#version 330 core

in vec3 vertPosition;
in vec3 vertNormal;
in vec2 vertUV;

uniform sampler2D diffuse0;
uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
    if (texture(diffuse0, vertUV).a < 0.1) discard;
    FragColor = texture(diffuse0, vertUV);   
}