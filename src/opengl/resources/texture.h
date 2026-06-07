#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

#include "opengl/resources/shader.h"
#include "opengl/format.h"

#include <iostream>

class Texture
{
public:
    Texture(textureType type);

    void Bind(GLuint texUnit) const;
    void Unbind() const;

    void genRGBATexture(const unsigned char* data, int imgWidth, int imgHeight);
    
    void linkUni(const Shader& shader, const char* uniformName, GLuint texUnit) const;

    textureType getType() const;

    void Delete();
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    GLuint ID = 0;
    textureType type;

    int imgWidth = 0;
    int imgHeight = 0;
    unsigned char* data = nullptr;

    bool textureGenerated = false;

};

#endif