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
	Bind();
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
	Unbind();
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
		std::cout << "VAO already empty or deleted" << std::endl;
	}
}

VAO::~VAO()
{
	Delete();
}
