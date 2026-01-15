#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	// Activates the Shader Program
	void Activate() const;
	// Deletes the Shader Program
	void Delete();
	// ID gettter
	GLuint getID() const;

private:
	// Reference ID of the Shader Program
	GLuint ID;
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};
#endif