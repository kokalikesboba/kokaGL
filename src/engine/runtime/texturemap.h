#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

#include "formats/rendererformat.hpp"

#include "opengl/resources/texture.h"

#include <memory>
#include <unordered_map>
#include <iostream>

class TextureMap
{
public:
    TextureMap();
    std::shared_ptr<Texture> GetOrAdd(const RenderFormat::TextureData& textureData);
protected:
    bool isCachedAndAlive(unsigned int texHash);
    std::shared_ptr<Texture> Add(
        const RenderFormat::TextureData& textureData
    );
    std::shared_ptr<Texture> Get(unsigned int texHash);
private:
    std::unordered_map<unsigned int, std::weak_ptr<Texture>> cache;

    std::shared_ptr<Texture> errorTex;
    int errorTexInstances = 0;
};

#endif