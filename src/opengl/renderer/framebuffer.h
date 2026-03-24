#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <opengl/buffers/vao.h>
#include <opengl/buffers/vbo.h>
#include <opengl/buffers/fbo.h>
#include <opengl/pipeline/shader.h>

class Framebuffer {
    public:
        Framebuffer(const double& width, const double& height);
        void RenderToFramebuffer() const;
        void FramebufferToWindow(const Shader& shader) const;
        ~Framebuffer();
    private:
        double width;
        double height;
        VAO vao;
        VBO vbo;
        FBO fbo;
        GLuint frameBufferTextureID;
        GLuint RBO;
};

#endif