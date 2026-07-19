#ifndef PNG_H
#define PNG_H

#include "stb/stb_img.h"
#include "math/hash.hpp"

#include <string>

class ParsePNG {
public:
    ParsePNG(const std::string& pngDir);
    ParsePNG(const unsigned char* pngData, const int dataLength);
    ~ParsePNG();
    ParsePNG(const ParsePNG&) = delete;
    ParsePNG& operator=(const ParsePNG&) = delete;
    unsigned char* data;
    int width, height;
    unsigned int hash;
};

#endif