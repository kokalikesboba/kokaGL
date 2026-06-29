#include"vbo.h"

VBO::VBO()
{
	glGenBuffers(1, &ID);
}

VBO::VBO(const std::vector<PNCUVertex> &vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PNCUVertex), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(const std::vector<PNUVertex> &vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PNUVertex), vertices.data(), GL_STATIC_DRAW);
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
        ID = 0;
    } else {
        std::cerr << "Attempted to delete a VBO with ID of 0" << std::endl;
    }
}

VBO::~VBO()
{
	Delete();
}

