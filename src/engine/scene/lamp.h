#ifndef LAMP_H
#define LAMP_H

#include "math/transform.h"

class Lamp : private Transform {
public:
    using Transform::SetPosition;
    using Transform::AddPosition;
    using Transform::GetPosition;

    using Transform::SetOrientation;
    using Transform::GetOrientation;
    using Transform::SetEulerRotation;
    using Transform::AddEulerRotation;
    using Transform::GetLocalAxis;
    using Transform::GetForwardAxis;

    Lamp(glm::vec3 color);
    // Kind of pointless when shaders exist, but whatever.
    void ChangeColor(glm::vec3 color);
    glm::vec3 GetColor();

private:
    glm::vec3 color = {1.f, 1.f, 1.f};
};

#endif