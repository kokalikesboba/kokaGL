#include"vbo.h"

VBO::VBO()
{
	glGenBuffers(1, &ID);
}

VBO::VBO(const std::vector<Vertex> &vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(),GL_STATIC_DRAW);
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0; // Crucial: Reset to 0 so we don't delete it twice
    } else {
        std::cerr << "Attempted to delete a VBO with ID of 0" << std::endl;
    }
}

VBO::~VBO()
{
	Delete();
}

