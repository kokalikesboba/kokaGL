#ifndef PNG_H
#define PNG_H

#include "stb/stb_img.h"

#include <string>

class ParsePNG {
public:
    ParsePNG(const std::string& pngDir);
    ParsePNG(const unsigned char* pngData, const int dataLength);
    ~ParsePNG();
    unsigned char* data;
    int width, height;
};

#endif