#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aUV;

out vec3 vertPosition;
out vec3 vertNormal;
out vec2 vertUV;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

void main()
{
    vertNormal = vec3(modelMatrix * vec4(aNormal, 0.0));
    vertUV = aUV;

    // 2. Calculate current world position
    vertPosition = vec3(modelMatrix * vec4(aPos, 1.0f));
    
    // 4. Final screen position
    gl_Position = cameraMatrix * vec4(vertPosition, 1.0);
}