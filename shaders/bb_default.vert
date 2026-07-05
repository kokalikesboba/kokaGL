#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform mat4 cameraOrientation;

layout (std140) uniform viewportUBO {
    mat4 viewportMatrix;
    mat4 viewportOrientation;
    vec3 viewportPosition;
    float pad0;
};

out vec3 vertPosition;
out vec3 vertNormal;
out vec2 vertUV;

void main()
{
    vec2 scaleXY = vec2(length(modelMatrix[0].xyz), length(modelMatrix[1].xyz));
    vec3 offset = mat3(viewportOrientation) * (vec3(aPos.xy, 0.0) * vec3(scaleXY, 1.0));
    
    vertPosition = vec3(modelMatrix * vec4(0,0,0,1)) + offset;   // model's position + camera-aligned offset
    vertNormal = mat3(viewportOrientation) * vec3(0.0, 0.0, 1.0);  // faces the camera by construction
    vertUV = aUV;

    gl_Position = viewportMatrix * vec4(vertPosition, 1.0);
}