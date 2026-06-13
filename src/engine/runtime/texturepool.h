#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H

#include "stb/stb_img.h"
#include "opengl/resources/texture.h"

#include <string>
#include <vector>
#include <unordered_map>

class TexturePool
{
public:
    TexturePool();

    void Add(unsigned char& data, unsigned int  hash);
    void Delete(unsigned int hash);
    bool isCached() 

    std::shared_ptr<Texture> Get(unsigned int hash hash);
    
    ~TexturePool();
private:

    std::unordered_map<Texture, int> cache;

};

#endif