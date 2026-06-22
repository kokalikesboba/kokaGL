#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H

#include "stb/stb_img.h"
#include "opengl/resources/texture.h"

#include <memory>
#include <unordered_map>
#include <iostream>

// Default missing texture.
inline std::vector<unsigned char> fallbackPixels = {
    227, 66, 107, 255,  
    66, 94, 135, 255,
    66, 94, 135, 255,
    227, 66, 107, 255
};

 // This class is an observer that stores and gets textures from a texHash key. It is meant to decrease the amount of duplicates textures in video memory regardless of where they were sourced from.
class TexturePool
{
public:
    TexturePool();
    std::shared_ptr<Texture> Add(unsigned int texHash, TextureType textype, std::vector<unsigned char>& bytes, int width, int height);
    bool isCachedAndAlive(unsigned int texHash);
    std::shared_ptr<Texture> Get(unsigned int texHash);
private:

    std::unordered_map<unsigned int, std::weak_ptr<Texture>> cache;
    
    std::shared_ptr<Texture> errorTex;
    int errorTexInstances = 0;
};

#endif