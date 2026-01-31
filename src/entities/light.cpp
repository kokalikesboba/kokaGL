#include "light.h"

Light::Light(glm::vec3 color) : gizmo("assets/models/pointer")
{
    this->color = color;
}

const void Light::DrawGizmo(const Shader &shader)
{
    gizmo.Draw(shader);
}
