#include "framebuffer.h"

float rectangleVertices[] = {
	1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 1.0f,

	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 1.0f
};

void createFrameBufferTexture(GLuint framebufferTextureID) {
	glGenTextures(1,&framebufferTextureID);
	glBindTexture(GL_TEXTURE_2D, framebufferTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1500, 1500, 0 , GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTextureID, 0);
}

Framebuffer::Framebuffer() 
{
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);  
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    createFrameBufferTexture(framebufferTexture);
    
	unsigned int RBO; 
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1500,1500);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer error: " << fboStatus << std::endl; 
	}

}

void Framebuffer::RenderToScreen()
{
    fbo.Unbind();
    // framebufferProgram.Activate();
    glBindVertexArray(rectVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Framebuffer::RenderToFramebuffer()
{
    fbo.Bind();
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}
