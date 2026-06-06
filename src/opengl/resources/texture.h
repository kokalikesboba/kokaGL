#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "opengl/resources/shader.h"
#include "opengl/format.h"

#include <iostream>

    static  unsigned char fallbackPixels[] = {
        255, 0, 255, 255,  0, 0, 0, 255,    // Row 1: Pink, Black
        0, 0, 0, 255,     255, 0, 255,255     // Row 2: Black, Pink
    };

class Texture
{
public:
    Texture(textureType type);
    textureType getType() const;

    void Bind(GLuint texUnit) const;
    void Unbind() const;
    void linkUni(const Shader& shader, const char* uniformName, GLuint texUnit) const;
    void genRGBATexture(unsigned char* data);

    void Delete();
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    GLuint ID = 0;
    textureType type;
    
    int colorChannels = 4;
    int imgWidth = 2;
    int imgHeight = 2;
    unsigned char* data = fallbackPixels;

};

#endif