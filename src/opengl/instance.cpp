#include "instance.h"

void OpenGLInstance::PrintGPUSpecs()
{
    std::cout << "\n=== GPU SPECIFICATIONS ===" << "\n";

    GLint maxTextures;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
    std::cout << "Max texture units: " << maxTextures << "\n";
    
    GLint maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    std::cout << "Max texture size: " << maxTexSize << "x" << maxTexSize << "\n";
    
    GLint maxRBOSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRBOSize);
    std::cout << "Max renderbuffer size: " << maxRBOSize << "\n";
    
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    std::cout << "Viewport: " << viewport[2] << "x" << viewport[3] << "\n";
    
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GLSL version: " << glslVersion << "\n";
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    std::cout << "OpenGL version: " << glVersion << "\n";
    
    const GLubyte* vendor = glGetString(GL_VENDOR);
    std::cout << "Vendor: " << vendor << "\n";
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    std::cout << "Renderer: " << renderer << "\n";
    
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    std::cout << "Max vertex attributes: " << maxVertexAttribs << "\n";
    
    GLint maxUniformBlockSize;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUniformBlockSize);
    std::cout << "Max uniform block size: " << maxUniformBlockSize / 1024 << " KB" << "\n";
    
    std::cout << "========================\n" << "\n";
}
