#include "light.h"

Light::Light(glm::vec3 color) : gizmo("assets/models/pointer")
{
    position = {0,0,0};
    this->color = color;
}

void Light::Draw(const Shader &shader) const
{
    gizmo.Draw(shader);
}

void Light::LinkRotation(const Shader& shader, const char* uniform) const
{
    glm::vec3 direction = rotation * glm::vec3(0.0f, -1.0f, 0.0f);
    shader.Activate();
    glUniform3f(glGetUniformLocation(shader.getID(), uniform), direction.x, direction.y, direction.z);
}

void Light::LinkColor(const Shader& shader, const char* uniform) const
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

void Light::SetOrientation(glm::vec3 euler)
{
    glm::quat rotX = glm::angleAxis(euler.x, glm::vec3(1,0,0));
    glm::quat rotY = glm::angleAxis(euler.y, glm::vec3(0,1,0));
    rotation = rotY * rotX;
    gizmo.SetOrientation(euler);
}

void Light::Rotate(glm::vec3 delta) {
    glm::quat rotX = glm::angleAxis(delta.x, glm::vec3(1,0,0));
    glm::quat rotY = glm::angleAxis(delta.y, glm::vec3(0,1,0));
    rotation = rotY * rotX * rotation;
    gizmo.Rotate(delta);
}