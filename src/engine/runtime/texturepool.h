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

    void Add(unsigned int hash, textureType textype);
    void Delete(unsigned int hash);

    bool isCached(unsigned int hash); 
    std::shared_ptr<Texture> Get(unsigned int hash);
    
    ~TexturePool();
private:

    std::unordered_map<unsigned int, std::shared_ptr<Texture>> map;

};

#endif