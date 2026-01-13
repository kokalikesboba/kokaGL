#include "ebo.h"

EBO::EBO(const std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	Unbind();
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
		std::cout << "EBO already deleted or empty" << std::endl;	
	}
}

EBO::~EBO()
{
	Delete();
}