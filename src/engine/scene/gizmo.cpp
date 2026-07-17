#include "gizmo.h"

Gizmo::Gizmo(const std::string& imgDir)
{
    this->data = ParsePNG(imgDir).data;
}

const unsigned char *Gizmo::GetTexData()
{
    return data;
}
