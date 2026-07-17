#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

#include "engine/formats/rendererformat.hpp"

#include <iostream>

class Texture
{
public:
    Texture();
    void GenRGBATexture(RenderFormat::TexType textype, unsigned char* bytes, int imgWidth, int imgHeight);
    RenderFormat::TextureInfo GetType() const;

    void Bind(GLuint texUnit) const;
    void Unbind() const;

    void Delete();
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
private:
    GLuint ID = 0;
    RenderFormat::TextureInfo texInfo;
    bool generationCheck = false;
};

#endif