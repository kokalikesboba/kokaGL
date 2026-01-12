#include "texture.h"

unsigned char fallbackPixels[] = {
    255, 0, 255, 255,  0, 0, 0, 255,    // Row 1: Pink, Black
    0, 0, 0, 255,     255, 0, 255,255     // Row 2: Black, Pink
};

Texture::Texture(textureType type, GLuint slot)
{
	// Loads default texture
	imgWidth = 2;
	imgHeight = 2;
	colorChannels = 3;
	data = fallbackPixels;
	stbiLoaded = false;

	// Calculates proper enum vale
	unit = GL_TEXTURE0 + slot;

	glGenTextures(1, &ID);
	// There are many texture units, we are choosing to modify this one on our bind.
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::stbLoad(const char* fileName)
{
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	data = stbi_load(fileName, &imgWidth, &imgHeight, &colorChannels, 0);
	if (!data) {
		imgWidth = 2;
		imgHeight = 2;
		colorChannels = 4;
		data = fallbackPixels;
		std::cout << std::string(fileName) + " not found." << std::endl;
	} else {
		stbiLoaded = true;
	}
}

void Texture::genTexture(Shader shader)
{
	// Assigns the texture to a Texture Unit
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Check what type of color channels the texture has and load it accordingly
	if (colorChannels == 4)
		glTexImage2D
		(
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
	else if (colorChannels == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			imgWidth,
			imgHeight,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			data
		);
	else if (colorChannels == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			imgWidth,
			imgHeight,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			data
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);

	// REVIEW: If I decide to create a shared texture system, this will get in the way. 
	if (stbiLoaded) stbi_image_free(data);
}

void Texture::linkUni(const Shader& shader, const char *uniformName)
{
    GLuint uniformAdr = glGetUniformLocation(shader.ID, uniformName);
    glUniform1i(uniformAdr, (unit - GL_TEXTURE0));
}

void Texture::Bind()
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D,ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::Delete()
{
    if (ID != 0) {
		glDeleteTextures(1, &ID);
		ID = 0;
	} else {
		std::cout << "Texture was deleted or empty" << std::endl;
	}
}

Texture::~Texture()
{
	Delete();
}
