#ifndef PNG_H
#define PNG_H

#include "stb/stb_img.h"
#include "math/hash.hpp"

#include <string>
#include <memory>

class ParsePNG {
public:
    ParsePNG(const std::string& pngDir, bool flipVertically = false);
    ParsePNG(const unsigned char* pngData, const int dataLength, bool flipVertically = false);

    ParsePNG(const ParsePNG&) = delete;
    ParsePNG& operator=(const ParsePNG&) = delete;
    
    std::unique_ptr<unsigned char[], decltype([](unsigned char* p) { stbi_image_free(p); })> data;
    int width, height;
    unsigned int hash;
private:
    bool flipVertically = false;
};

#endif