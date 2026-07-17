#ifndef GIZMO_H
#define GIZMO_H

#include "math/transform.h"
#include "engine/parsers/png.h"

#include <vector>

class Gizmo : private Transform {
public:
    using Transform::SetPosition;
    using Transform::AddPosition;
    using Transform::GetPosition;

    using Transform::SetScale;
    using Transform::GetScale;

    Gizmo(const std::string& imgDir);
    const unsigned char* GetTexData() const;
private:
    std::vector<unsigned char> data;
    int width = 0, height = 0;
};
#endif