#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

#include "formats/renderformat.hpp"

#include <iostream>

class Texture
{
public:
    Texture();
    void GenRGBATexture(RenderFormat::TexType textype, const unsigned char* bytes, int imgWidth, int imgHeight);
    RenderFormat::TexType GetType() const;

    void Bind(GLuint texUnit) const;
    void Unbind() const;

    void Delete();
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
private:
    GLuint ID = 0;
    RenderFormat::TextureData texData;
    bool generationCheck = false;
};

#endif