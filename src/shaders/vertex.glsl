#version 330 core
layout(location = 0) in vec3 aPos;

layout(std140) uniform Globals {
    mat4 viewProj;
    vec4 color;
};

void main() {
    gl_Position = viewProj * vec4(aPos, 1.0);
}