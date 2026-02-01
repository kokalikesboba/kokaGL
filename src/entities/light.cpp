#include "light.h"

Light::Light(glm::vec3 color) : gizmo("assets/models/pointer")
{
    position = {0,0,0};
    rotation = {0,0,0};
    this->color = color;
}

const void Light::DrawGizmo(const Shader &shader)
{
    gizmo.Draw(shader);
}

const void Light::LinkRotation(const Shader& shader, const char* uniform)
{
    shader.Activate();
    glUniform3f(glGetUniformLocation(shader.getID(), uniform), rotation.x, rotation.y, rotation.z);
}

const void Light::LinkColor(const Shader& shader, const char* uniform)
{
    shader.Activate();
    glUniform3f(glGetUniformLocation(shader.getID(), uniform), color.r, color.g, color.b);
}

void Light::SetPosition(glm::vec3 position)
{
    this->position = position;
    gizmo.SetPosition(position);
}

void Light::Translate(glm::vec3 translate)
{
    this->position += translate;
    gizmo.Translate(translate);
}

void Light::SetOrientation(glm::vec3 rotation)
{
    this->rotation = rotation;
    gizmo.SetOrientation(rotation);
}

void Light::Rotate(glm::vec3 rotation)
{
    this->rotation += rotation;
    gizmo.Rotate(rotation);
}
