#version 330 core

out vec4 FragColor;

void main() {

    float depth = gl_FragCoord.z;

    FragColor = depth * vec4(1.0, 1.0, 1.0, 1.0);
} 