#include "png.h"

#include <iostream>

ParsePNG::ParsePNG(const std::string &pngDir, bool flipVertically)
{
    stbi_set_flip_vertically_on_load(flipVertically);

    data.reset(stbi_load(pngDir.c_str(), &width, &height, nullptr, colorChannels));

    if (data == nullptr) throw std::runtime_error("[ERROR][ParsePNG] Failed to decode image from path");

    hash = Hash::djb2(data.get(), size);

    size = colorChannels * width * height;

    // TODO: I've resigned to doing a deep copy of the loaded data because I got skill issued by m_alloc's ownership and lifetime problems. I'm neither satisfied with STB and I think that RenderFormat::TextureData should just carry a pointer or a reference to texture data.
    bytes.assign(data.get(), data.get() + size);
}

ParsePNG::ParsePNG(const unsigned char *pngData, const int dataLength, bool flipVertically)
{
    stbi_set_flip_vertically_on_load(flipVertically);

    data.reset(stbi_load_from_memory(pngData, dataLength, &this->width, &this->height, nullptr, colorChannels));

    if (data == nullptr) throw std::runtime_error("[ERROR][ParsePNG] Failed to decode image from memory");

    hash = Hash::djb2(data.get(), dataLength);

    size = colorChannels * width * height;
    bytes.assign(data.get(), data.get() + size);
}