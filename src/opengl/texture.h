#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include "stb/stb_img.h"
#include "shader.h"

#include <iostream>

enum class textureType {
    Diffuse,
    Specular,
};

class Texture
{
public:

    textureType type;

    // Construct a texture object, it takes a texture unit (0-15).
    Texture(textureType type, GLuint slot);
    // Loads a texture from a directory into texture data buffer. 
    // REVIEW: Do NOT load a texture twice
    void stbLoad(const char* image);
    // Buffers texture data into OpenGL
    void genTexture(Shader shader);
    // Links texture to uniform
    void linkUni(const Shader& shader, const char* uniformName);
    // Binds
    void Bind();
    // Unbinds
    void Unbind();
    // Cleans up texture on GPU side.
    void Delete();
    ~Texture();
private:

    GLuint ID;
    GLuint unit;

    int colorChannels;
    int imgWidth;
    int imgHeight;
    unsigned char* data;
    bool stbiLoaded;
};

#endif