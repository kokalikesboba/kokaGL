#include "renderer.h"

static void PrintError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    std::cout << std::string(message) << std::endl;
}

Renderer::Renderer()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(PrintError, 0);
}

void Renderer::PrintGPUSpecs()
{
    std::cout << "\n=== GPU SPECIFICATIONS ===" << std::endl;

    GLint maxTextures;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
    std::cout << "Max texture units: " << maxTextures << std::endl;
    
    GLint maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    std::cout << "Max texture size: " << maxTexSize << "x" << maxTexSize << std::endl;
    
    GLint maxRBOSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRBOSize);
    std::cout << "Max renderbuffer size: " << maxRBOSize << std::endl;
    
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    std::cout << "Viewport: " << viewport[2] << "x" << viewport[3] << std::endl;
    
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GLSL version: " << glslVersion << std::endl;
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    std::cout << "OpenGL version: " << glVersion << std::endl;
    
    const GLubyte* vendor = glGetString(GL_VENDOR);
    std::cout << "Vendor: " << vendor << std::endl;
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    std::cout << "Renderer: " << renderer << std::endl;
    
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    std::cout << "Max vertex attributes: " << maxVertexAttribs << std::endl;
    
    GLint maxUniformBlockSize;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUniformBlockSize);
    std::cout << "Max uniform block size: " << maxUniformBlockSize / 1024 << " KB" << std::endl;
    
    std::cout << "========================\n" << std::endl;
}
