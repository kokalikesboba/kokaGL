#ifndef PNG_H
#define PNG_H

#include "stb/stb_img.h"
#include "math/hash.hpp"

#include <string>
#include <memory>
#include <vector>
#include <cstdint>

class ParsePNG {
public:
    ParsePNG(const std::string& pngDir, bool flipVertically = false);
    ParsePNG(const unsigned char* pngData, const int dataLength, bool flipVertically = false);

    ParsePNG(const ParsePNG&) = delete;
    ParsePNG& operator=(const ParsePNG&) = delete;
    
    std::vector<unsigned char> bytes;
    // TODO: Need to review widths for these. This is a ticking time bomb for bigger textures.
    int width;
    int height;
    unsigned int hash;
    // (in bytes)
    int size;
private:
    const int colorChannels = 4;
    std::unique_ptr<unsigned char[], decltype([](unsigned char* p) { stbi_image_free(p); })> data;
    bool flipVertically = false;
};

#endif