#include "png.h"

#include <iostream>

ParsePNG::ParsePNG(const std::string &pngDir)
{
    stbi_set_flip_vertically_on_load(true);

    data = stbi_load(pngDir.c_str(), &width, &height, nullptr, 4);

    stbi_set_flip_vertically_on_load(false);

    if (data == nullptr) {
        width = 0;
        height = 0;
        hash = 0;
        std::cerr << "[WARN][ParsePNG] Failed to decode PNG file: " << pngDir << std::endl;
        return; // keep hash at 0 so the pool serves the fallback texture
    }

    hash = Hash::djb2(data, static_cast<size_t>(width) * height * 4);
}

ParsePNG::ParsePNG(const unsigned char *pngData, const int dataLength)
{
    stbi_set_flip_vertically_on_load(true);

    data = stbi_load_from_memory(pngData, dataLength, &this->width, &this->height, nullptr, 4);

    stbi_set_flip_vertically_on_load(false);

    if (data == nullptr) {
        width = 0;
        height = 0;
        hash = 0;
        std::cerr << "[WARN][ParsePNG] Failed to decode PNG from memory (" << dataLength << " bytes)" << std::endl;
        return; // keep hash at 0 so the pool serves the fallback texture
    }

    hash = Hash::djb2(data, static_cast<size_t>(width) * height * 4);
}

ParsePNG::~ParsePNG()
{
    stbi_image_free(data);
}
