#include "gizmo.h"

#include <iostream>

Gizmo::Gizmo(const std::string& imgDir)
{
    ParsePNG png(imgDir);
    textureData.width = png.width;
    textureData.height = png.height;
    // TODO: missing texturepool integration;
    textureData.hash = 0;
    textureData.bytes.assign(png.data, png.data + (png.width * png.height * 4));
}

const RenderFormat::TextureData *Gizmo::GetTexData() const
{
    return &textureData;
}