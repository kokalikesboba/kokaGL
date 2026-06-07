#include"vao.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(
	const VBO& VBO,
	const GLuint& layout,
	const GLuint& numComponents,
	const GLenum& type,
	const GLsizeiptr& stride,
	const void* offset) const
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
}

void VAO::Bind() const
{
	glBindVertexArray(ID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	if (ID != 0) {
		glDeleteVertexArrays(1, &ID);
		ID = 0;
	} else {
		std::cerr << "Attempted to deleted a VAO with ID of 0" << std::endl;
	}
}

VAO::~VAO()
{
	Delete();
}
