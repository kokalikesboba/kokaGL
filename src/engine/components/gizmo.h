#ifndef GIZMO_H
#define GIZMO_H

#include "opengl/drawable/billboard.h"
#include "opengl/resources/shader.h"

std::vector<PNUVertex> vertices = {
    // position                  normal             uv
    {{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // top right
    {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // top left
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // bottom left
    {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // bottom right
};

std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 3, 0
};

class Gizmo {
public:
    Gizmo(const std::string imgDir);
    void Draw();
private:
    Shader gizmoShader;
    Billboard billboard;
    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f, 1.f, 1.f};
};
#endif  