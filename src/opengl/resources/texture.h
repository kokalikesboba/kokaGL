#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

#include "opengl/resources/shader.h"
#include "opengl/format.h"

#include <iostream>
#include <vector>

class Texture
{
public:
    Texture(TextureType type);

    void Bind(GLuint texUnit) const;
    void Unbind() const;

    void genRGBATexture(unsigned char* bytes, int imgWidth, int imgHeight);
    
    void linkUni(const Shader& shader, const char* uniformName, GLuint texUnit) const;

    TextureType getType() const;

    void Delete();
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    GLuint ID = 0;
    TextureType type;

    int width = 0;
    int height = 0;

    bool textureGenerated = false;

};

#endif