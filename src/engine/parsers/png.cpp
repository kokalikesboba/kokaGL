#include "png.h"

ParsePNG::ParsePNG(const std::string &pngDir)
{
    stbi_set_flip_vertically_on_load(true);
    
    data = stbi_load(pngDir.c_str(), &width, &height, nullptr, 4);

    stbi_set_flip_vertically_on_load(false);
}

ParsePNG::ParsePNG(const unsigned char *pngData, const int dataLength)
{
    stbi_set_flip_vertically_on_load(true);

    data = stbi_load_from_memory(pngData, dataLength, &this->height, &this->height, nullptr, 4);

    stbi_set_flip_vertically_on_load(false);
}

ParsePNG::~ParsePNG()
{
    stbi_image_free(data);
}
