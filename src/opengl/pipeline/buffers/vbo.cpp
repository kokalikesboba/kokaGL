#include"vbo.h"

VBO::VBO(const std::vector <Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(),GL_STATIC_DRAW);
	Unbind();
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
        std::cout << "VBO already empty or deleted." << std::endl;
    }
}

VBO::~VBO()
{
	Delete();
}

