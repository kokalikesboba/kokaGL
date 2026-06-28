#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 crntPosition;
out vec3 vertexNormal;
out vec2 texCoord;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

void main()
{
    vertexNormal = vec3(modelMatrix * vec4(aNormal, 0.0));
    texCoord = aTex;

    // 2. Calculate current world position
    crntPosition = vec3(modelMatrix * vec4(aPos, 1.0f));
    
    // 4. Final screen position
    gl_Position = cameraMatrix * vec4(crntPosition, 1.0);
}