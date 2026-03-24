#include "fbo.h"

FBO::FBO()
{
	glGenFramebuffers(1, &ID);
}

void FBO::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FBO::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Delete()
{
    if (ID != 0) {
		glDeleteFramebuffers(1, &ID);
		ID = 0;
	} else {
		std::cout << "FBO already empty or deleted" << std::endl;
	}
}

FBO::~FBO()
{
    Delete();
}
