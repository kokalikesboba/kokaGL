#include "ubo.h"

UBO::UBO(const std::vector<float>& data, unsigned int )
{	
	glGenBuffers(1, &ID);
	Bind();
	glBufferData(
		GL_UNIFORM_BUFFER,
		data.size() *  sizeof(float),
		data.data(),
		GL_STATIC_DRAW
	);
	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, ID);
	Unbind();
}

void UBO::LinkUni(const Shader &shader, const char *uniform) const
{
	GLuint blockIndex = glGetUniformBlockIndex(shader.getID(), uniform);
	glUniformBlockBinding(shader.getID(), blockIndex, 0);

}

void UBO::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, ID);
}

void UBO::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::Delete()
{
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0; // Reset to 0 so we don't delete it twice
    } else {
        std::cout << "UBO already empty or deleted." << std::endl;
    }
}

UBO::~UBO()
{
	Delete();
}

