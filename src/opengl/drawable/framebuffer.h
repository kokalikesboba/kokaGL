#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <opengl/buffers/vao.h>
#include <opengl/buffers/vbo.h>
#include <opengl/buffers/fbo.h>
#include <opengl/resources/shader.h>

class Framebuffer {
    public:
        Framebuffer(const double& width, const double& height);
        void DrawToFramebuffer() const;
        void DrawToTarget(const Shader& shader, Framebuffer& target) const;
        void DrawToWindow(const Shader& shader) const;
        ~Framebuffer();
    private:
        double width;
        double height;
        VAO vao;
        VBO vbo;
        FBO fbo;
        // Implicitly created resources that aren't super relevant for the rest of the pipeline.
        GLuint frameBufferTextureID;
        GLuint RBO;
};

#endif