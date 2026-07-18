#include "lamp.h"

Lamp::Lamp(glm::vec3 color)
{
    this->color = color;
}

void Lamp::ChangeColor(glm::vec3 color)
{
    this->color = color;
}

glm::vec3 Lamp::GetColor()
{
    return color;
}