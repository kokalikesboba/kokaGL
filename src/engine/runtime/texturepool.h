#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H

#include "formats/rendererformat.hpp"

#include "opengl/resources/texture.h"

#include <memory>
#include <unordered_map>
#include <iostream>

 // This class is an observer that stores and gets textures from a texHash key. It is meant to decrease the amount of duplicates textures in video memory regardless of where they were sourced from.
class TexturePool
{
public:
    TexturePool();
    std::shared_ptr<Texture> GetOrAdd(const RenderFormat::TextureData& textureData);
private:
    bool isCachedAndAlive(unsigned int texHash);
    std::shared_ptr<Texture> Add(
        const RenderFormat::TextureData& textureData
    );
    std::shared_ptr<Texture> Get(unsigned int texHash);

    std::unordered_map<unsigned int, std::weak_ptr<Texture>> cache;

    std::shared_ptr<Texture> errorTex;
    int errorTexInstances = 0;
};

#endif