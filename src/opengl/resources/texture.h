#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

#include "opengl/format.h"
#include "opengl/resources/shader.h"

#include <iostream>
#include <vector>

class Texture
{
public:
    Texture(PBRTexType type);

    void Bind(GLuint texUnit) const;
    void Unbind() const;

    void genRGBATexture(unsigned char* bytes, int imgWidth, int imgHeight);

    PBRTexType getType() const;

    void Delete();
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    GLuint ID = 0;
    PBRTexType type;

    int width = 0;
    int height = 0;

    // Generation check on bind.
    bool textureGenerated = false;
};

#endif