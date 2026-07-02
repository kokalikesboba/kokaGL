#version 330 core
out vec4 FragColor;

in vec3 crntPosition;
in vec3 vertexNormal;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform vec3 cameraPos;

void main()
{
    FragColor = vec4(0.f,0.f,0.f, 1.f);
}
  