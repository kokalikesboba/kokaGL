#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <opengl/buffers/fbo.h>

class Framebuffer {
    public:
        Framebuffer();
        void RenderToScreen();
        void RenderToFramebuffer();
    private:
        unsigned int rectVAO, rectVBO;
        FBO fbo;
        GLuint texture = 0;
        GLuint framebufferTexture = 0;
};

#endif