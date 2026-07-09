#ifndef GIZMO_H
#define GIZMO_H

#include "math/transform.h"
#include "opengl/drawable/billboard.h"
#include "opengl/resources/shader.h"

#include "stb/stb_img.h"

class Gizmo : private Transform {
public:
    using Transform::SetPosition;
    using Transform::AddPosition;
    using Transform::GetPosition;

    using Transform::SetScale;
    using Transform::GetScale;

    Gizmo(const std::string imgDir);
    void Draw(Shader& shader);
private:
    std::unique_ptr<Texture> texture;
    std::unique_ptr<Billboard> billboard;

    int width, height = 0;
};
#endif