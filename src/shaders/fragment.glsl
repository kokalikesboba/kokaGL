#version 330 core
out vec4 FragColor;

layout(std140) uniform Globals {
    mat4 viewProj;
    vec4 color;
};

void main() {
    FragColor = color; // should be white from your UBO
}