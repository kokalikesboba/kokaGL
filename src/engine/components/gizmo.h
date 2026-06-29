#ifndef GIZMO_H
#define GIZMO_H

#include "opengl/drawable/billboard.h"
#include "opengl/resources/shader.h"

#include <filesystem>

class Gizmo {
public:
    Gizmo(const std::string imgDir);
    void Draw();
private:
    Shader gizmoShader;
    std::unique_ptr<Texture> texture;
    std::unique_ptr<Billboard> billboard;

    int width, height = 0;
    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f, 1.f, 1.f};
};
#endif  