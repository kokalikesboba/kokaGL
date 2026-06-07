#include "texture.h"

Texture::Texture(textureType type)
{
	this->type = type;
	glGenTextures(1, &ID);
}

void Texture::Bind(GLuint texUnit) const
{
	GLuint unit = GL_TEXTURE0 + texUnit;
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D,ID);
	// quick hack
	if (!textureGenerated) std::cerr << "Texture: " << ID << " was bound, but not generated." << std::endl;
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::genRGBATexture(const unsigned char *data, int imgWidth, int imgHeight)
{
	glBindTexture(GL_TEXTURE_2D,ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D (
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		imgWidth,
		imgHeight,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);

	textureGenerated = true;
}

void Texture::linkUni(const Shader& shader, const char *uniformName, GLuint texUnit) const
{
	GLuint uniformAdr = glGetUniformLocation(shader.getID(), uniformName);
    glUniform1i(uniformAdr, texUnit);
}

textureType Texture::getType() const
{
	return type;
}


void Texture::Delete()
{
    if (ID != 0) {
		glDeleteTextures(1, &ID);
		ID = 0;
	} else {
		std::cerr << "Attempted to delete a texture with ID of 0" << std::endl;
	}
}

Texture::~Texture()
{
	Delete();
}