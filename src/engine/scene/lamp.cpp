#include "lamp.h"

Lamp::Lamp()
{
}

Lamp::Lamp(glm::vec4 color)
{
    this->color = color;
}

void Lamp::SetColor(glm::vec4 color)
{
    this->color = color;
}

glm::vec4 Lamp::GetColor()
{
    return color;
}

void Lamp::SetType(int type)
{
    this->type = type;
}

int Lamp::GetType()
{
    return this->type;
}
