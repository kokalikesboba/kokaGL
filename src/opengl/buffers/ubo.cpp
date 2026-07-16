#include "ubo.h"

UBO::UBO(GLsizeiptr byteSize, GLuint slot)
{
	this->byteSize = byteSize;
	this->slot = slot;

	glGenBuffers(1, &ID);
	Bind();
	// Allocate only; contents come from Update() each frame.
	glBufferData(GL_UNIFORM_BUFFER, byteSize, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, ID);
}

void UBO::LinkBlock(const Shader& shader, GLuint ID) const
{
	glUniformBlockBinding(shader.GetID(), ID, slot);
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
        std::cerr << "[ERROR][UBO] Attempted to delete a UBO with ID of 0" << std::endl;
    }
}

UBO::~UBO()
{
	Delete();
}
