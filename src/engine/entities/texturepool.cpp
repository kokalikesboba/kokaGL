#include "texturepool.h"

/* 
void Texture::stbLoad(std::string fileName)
{
	this->fileName = fileName;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	data = stbi_load(fileName.c_str(), &imgWidth, &imgHeight, &colorChannels, 0);
	if (!data) {
		imgWidth = 2;
		imgHeight = 2;
		colorChannels = 4;
		data = fallbackPixels;
		if (verboseOutput) std::cout << "STB: " + std::string(fileName) + " not found." << std::endl;
	} else {
		stbiLoaded = true;
	}
}

void Texture::genTexture()
{
	Bind();
	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Check what type of color channels the texture has and load it accordingly
	if (stbiLoaded) {
			if (colorChannels == 4) {

			if (verboseOutput) std::cout << "TEX: " + fileName + " loaded with 4 channels" << std::endl;
		} else if (colorChannels == 3) {
			glTexImage2D (
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
			if (verboseOutput) std::cout << "TEX: " + fileName + " loaded with 3 channels" << std::endl;
		} else if (colorChannels == 1) {
			glTexImage2D (
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
			if (verboseOutput) std::cout << "TEX: " + fileName + " loaded with 1 channels" << std::endl;
		} else {
			throw std::invalid_argument("Automatic Texture type recognition failed");
		}
	} else {
	// FALLBACK BRANCH
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
	if (verboseOutput) std::cout << "TEX: Using fallback for " + fileName << std::endl;
}

	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	Unbind();

	// REVIEW: If I decide to create a shared texture system, this will get in the way. 
	if (stbiLoaded) stbi_image_free(data);
}*/