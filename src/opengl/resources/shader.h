#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
	Shader(const std::string& vertFile, const std::string& fragFile);
	void Activate() const;
	void Reload();
	void Delete();
	GLuint getID() const;
	~Shader();

private:
	GLuint ID;
	std::string vertFile;
	std::string fragFile;
	void compileErrors(unsigned int shader, const char* type);
};
#endif