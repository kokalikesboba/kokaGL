#include "gizmo.h"

#include <iostream>

Gizmo::Gizmo(const std::string& imgDir)
{
    ParsePNG png(imgDir, false);
    textureData.width = png.width;
    textureData.height = png.height;
    textureData.hash = png.hash;
    textureData.bytes = std::move(png.bytes);
}

const RenderFormat::TextureData *Gizmo::GetTexData() const
{
    return &textureData;
}