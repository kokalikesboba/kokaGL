#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"

#include <iostream>

class Renderer {
public:
    Renderer();
    void PrintGPUSpecs();
    ~Renderer();
private:
    static void PrintError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
    bool DEBUG = false;
};

#endif