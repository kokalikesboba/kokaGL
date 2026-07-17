#ifndef GIZMO_H
#define GIZMO_H

#include "math/transform.h"
#include "engine/parsers/png.h"

class Gizmo : private Transform {
public:
    using Transform::SetPosition;
    using Transform::AddPosition;
    using Transform::GetPosition;

    using Transform::SetScale;
    using Transform::GetScale;

    Gizmo(const std::string& imgDir);
    const unsigned char* GetTexData();
private:
    unsigned char* data;
};
#endif