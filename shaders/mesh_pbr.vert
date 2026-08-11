#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aUV;

layout (std140) uniform viewportUBO {
    mat4 viewportMatrix;
    mat4 viewportOrientation;
    vec3 viewportPosition;
};

struct Light {
    vec4 color;
    vec3 position;
    int  pad;
    vec3 direction;
    int  type;
};

layout (std140) uniform lightUBO {
    Light lights[4];
};

uniform mat4 modelMatrix;

out vec3 vertPosition;
out vec3 vertNormal;
out vec2 vertUV;

void main()
{
    vertNormal = vec3(modelMatrix * vec4(aNormal, 0.0));
    vertUV = aUV;

    // 2. Calculate current world position
    vertPosition = vec3(modelMatrix * vec4(aPos, 1.0f));
    
    // 4. Final screen position
    gl_Position = viewportMatrix * vec4(vertPosition, 1.0);
}