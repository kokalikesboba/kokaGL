#include "gizmo.h"

#include <iostream>

Gizmo::Gizmo(const std::string& imgDir)
{
    ParsePNG png(imgDir);
    if (png.data != nullptr) {
        data.assign(png.data, png.data + static_cast<size_t>(png.width) * png.height * 4);
        width = png.width;
        height = png.height;
    } else {
        std::cerr << "[WARN][Gizmo] No pixel data for: " << imgDir << std::endl;
    }
}

const unsigned char* Gizmo::GetTexData() const
{
    return data.empty() ? nullptr : data.data();
}
