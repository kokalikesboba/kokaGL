#ifndef GIZMO_H
#define GIZMO_H

#include "engine/formats/rendererformat.hpp"
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
    const RenderFormat::TextureData* GetTexInfo() const;
private:
    RenderFormat::TextureData textureData;
};
#endif