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
    // TODO: Do NOT load a texture twice
    void stbLoad(const char* image);
    // Buffers texture data into OpenGL
    void genTexture();
    // Links texture to uniform
    void linkUni(const Shader& shader, const char* uniformName) const;
    // Binds
    void Bind() const;
    // Unbinds
    void Unbind() const;
    // Cleans up texture on OpenGL's side.
    void Delete();
    ~Texture();

    // Make non-copyable
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:

    GLuint ID = 0;
    GLuint unit = 0;

    int colorChannels = 0;
    int imgWidth = 0;
    int imgHeight = 0;
    unsigned char* data = nullptr;
    bool stbiLoaded = false;
};

#endif