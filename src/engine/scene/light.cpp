#include "light.h"

Light::Light(glm::vec3 color)
{
    this->color = color;
}

void Light::ChangeColor(glm::vec3 color)
{
    this->color = color;
}

glm::vec3 Light::GetColor()
{
    return color;
}