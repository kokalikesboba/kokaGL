#include "png.h"

#include <iostream>

ParsePNG::ParsePNG(const std::string &pngDir, bool flipVertically)
{
    stbi_set_flip_vertically_on_load(flipVertically);
    data.reset(stbi_load(pngDir.c_str(), &width, &height, nullptr, 4));

    if (data == nullptr) throw std::runtime_error("[ERROR][ParsePNG] Failed to decode image from path");

    hash = Hash::djb2(data.get(), static_cast<size_t>(width) * height * 4);
}

ParsePNG::ParsePNG(const unsigned char *pngData, const int dataLength, bool flipVertically)
{

    data.reset(stbi_load_from_memory(pngData, dataLength, &this->width, &this->height, nullptr, 4));

    if (data == nullptr) throw std::runtime_error("[ERROR][ParsePNG] Failed to decode image from memory");

    hash = Hash::djb2(data.get(), static_cast<size_t>(width) * height * 4);
}