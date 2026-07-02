#include "light.h"

Light::Light(glm::vec3 color)
{
    this->color = color;

    glm::quat rotX = glm::angleAxis(180.f, glm::vec3(1,0,0));
    orientation *= rotX;
}

void Light::Draw(const Shader &shader) const
{

}

void Light::SetPosition(glm::vec3 position)
{
    this->position = position;
    //.SetPosition(position);
}

void Light::Translate(glm::vec3 translate)
{
    this->position += translate;
    //gizmo.SetPosition(translate);
}

void Light::SetOrientation(glm::vec3 euler)
{
    glm::quat rotX = glm::angleAxis(euler.x, glm::vec3(1,0,0));
    glm::quat rotY = glm::angleAxis(euler.y, glm::vec3(0,1,0));
    orientation = rotY * rotX;
    //gizmo.SetOrientation(euler);
}

void Light::Rotate(glm::vec3 delta) {
    glm::quat rotX = glm::angleAxis(delta.x, glm::vec3(1,0,0));
    glm::quat rotY = glm::angleAxis(delta.y, glm::vec3(0,1,0));
    orientation = rotY * rotX * orientation;
    //gizmo.SetOrientation(delta);
}

glm::vec3 Light::getColor()
{
    return color;
}

glm::vec3 Light::getOrientation()
{
    return orientation * glm::vec3(0.f, -1.0f, 0.f);
}
