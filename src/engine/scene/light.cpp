#include "light.h"

Light::Light(glm::vec3 color)
{
    this->color = color;
}

void Light::Draw(const Shader &shader) const
{

}

glm::vec3 Light::getColor()
{
    return color;
}