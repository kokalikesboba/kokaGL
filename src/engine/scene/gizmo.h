#ifndef GIZMO_H
#define GIZMO_H

#include "math/transform.h"
#include "opengl/drawable/billboard.h"
#include "opengl/resources/shader.h"

#include "stb/stb_img.h"

class Gizmo : public Transform {
public:
    Gizmo(const std::string imgDir);
    void Draw(Shader& gizmoShader);
private:
    std::unique_ptr<Texture> texture;
    std::unique_ptr<Billboard> billboard;

    int width, height = 0;
};
#endif  