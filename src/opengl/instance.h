#ifndef INSTANCE_H
#define INSTANCE_H

#include "glad/glad.h"

#include <stdexcept>
#include <iostream>

static void PrintError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    std::cout << std::string(message) << "\n";
}

class OpenGLInstance {
public:
    OpenGLInstance();
    void PrintGPUSpecs();
    ~OpenGLInstance();
};

#endif