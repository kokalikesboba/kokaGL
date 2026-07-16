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
	template <typename T> void UploadUni(const std::string& uniformName, const T& value);
	void Delete();
    GLuint GetUniformBlockIndex(const std::string& uniformBlockName);
	GLuint GetID() const;
	~Shader();

private:
	GLuint ID;
	std::string shaderName;
	std::string vertFile;
	std::string fragFile;
	void compileErrors(unsigned int shader, const char* type);
	std::unordered_map<std::string, GLint> uniformLocationCache;

	bool printConsole = true;

	void UniformType(GLint loc, const glm::mat4& m) { glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m)); }
	void UniformType(GLint loc, const glm::vec3& v) { glUniform3fv(loc, 1, glm::value_ptr(v)); }
	void UniformType(GLint loc, const float f) { glUniform1f(loc, f); }
	void UniformType(GLint loc, const int i) { glUniform1i(loc, i); }
};

template <typename T>
inline void Shader::UploadUni(const std::string &uniformName, const T &value)
{
	Activate();
	GLint loc;
	auto it = uniformLocationCache.find(uniformName);
	if (it == uniformLocationCache.end()) {
		// GLint returns -1 when uniform is invalid
		loc = glGetUniformLocation(ID, uniformName.c_str());
		if (loc == -1) {	
			if (printConsole) {
				std::cerr << "[WARNING][SHADER] Unknown uniform (" << uniformName << ") in: " << shaderName << std::endl;
				printConsole = false;
			}
			return;
		}
		std::cerr << "[VERBOSE][SHADER] Uniform: " << uniformName << " inserted into " << shaderName << std::endl;
		uniformLocationCache.insert({uniformName, loc});
	} else {
		loc = it->second;
	}
	UniformType(loc, value);
}

#endif