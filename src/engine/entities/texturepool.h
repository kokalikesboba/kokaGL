#ifndef TEXTUREPOOL
#define TEXTUREPOOL

#include "stb/stb_img.h"
#include "opengl/resources/texture.h"

#include <string>
#include <vector>
#include <unordered_map>

class TexturePool
{
public:
    
private:
    std::vector<texEntry>pool;

	bool stbiLoaded = false;
    std::string fileName;
    unsigned char* data = nullptr;
    
};

#endif