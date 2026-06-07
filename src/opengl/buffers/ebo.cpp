#include "ebo.h"

EBO::EBO(const std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	if (ID != 0) {
		glDeleteBuffers(1, &ID);
		ID = 0;
	} else {
		std::cerr << "Attempted to delete an EBO with ID of 0" << std::endl;	
	}
}

EBO::~EBO()
{
	Delete();
}