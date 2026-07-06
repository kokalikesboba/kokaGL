#version 330 core

out vec4 FragColor;

void main() {

    float near = 0.05;
    float far = 3.0;
    float depth = gl_FragCoord.z;

    float ndcDepth = depth * 2.0 - 1.0;

    float linearDepth = (2.0 * near * far) / (far + near - ndcDepth * (far - near));

    FragColor = (1 - (linearDepth / far)) * vec4(1.0, 1.0, 1.0, 1.0);
} 