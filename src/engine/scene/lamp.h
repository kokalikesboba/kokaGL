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
    using Transform::GetEulerRotation;
    using Transform::AddEulerRotation;
    using Transform::GetLocalAxis;
    using Transform::GetForwardAxis;

    Lamp();
    Lamp(glm::vec4 color);
    // Kind of pointless when shaders exist, but whatever.
    void SetColor(glm::vec4 color);
    glm::vec4 GetColor();
    void SetType(int type);
    int GetType();

private:
    int type = 0;
    glm::vec4 color = {1.f, 1.f, 1.f,  1.f};
};

#endif