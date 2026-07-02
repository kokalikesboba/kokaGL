#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Shader
{
public:
	Shader(const std::string& vertFile, const std::string& fragFile);
	void Activate() const;
	void Reload();
	void uploadMat4(const std::string& uniformName, const glm::mat4 matrix);
	void uploadVec3(const std::string& uniformName, const glm::vec3 vector);
	void uploadFloat1(const std::string& uniformName, const float value);
	void Delete();
	GLuint getID() const;
	~Shader();

private:
	GLuint ID;
	std::string shaderName;
	std::string vertFile;
	std::string fragFile;
	void compileErrors(unsigned int shader, const char* type);
	std::unordered_map<std::string, GLint> uniformLocationCache;
};
#endif