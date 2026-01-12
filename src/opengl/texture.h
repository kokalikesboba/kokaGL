#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include "stb/stb_img.h"
#include "shader.h"

#include <iostream>

class Texture
{
public:

    const char* type;

    // Constructor is more stbi sided
    Texture(const char* image,  const char* texType, GLenum slot);
    // Shove that into OpenGL
    void texUnit(Shader shader, const char* uniform, GLuint unit);
    // Binds
    void Bind();
    // Unbinds
    void Unbind();
    // Cleaning
    void Delete();
    ~Texture();
private:
    GLuint ID;
    GLuint unit;
};

#endif