#ifndef UBO_H
#define UBO_H

#include <glad/glad.h>

#include "opengl/pipeline/shader.h"

#include <vector>
#include <iostream>

class UBO
{
public:
	// Constructs a VBO. This buffer will not remain bound after execution.
	UBO(const std::vector<float>& data, unsigned int slot);
	// Links Uniform
	void LinkUni(const Shader& shader,const char* uniform) const;
	// Binds the VBO
	void Bind() const;
	// Unbinds the VBO
	void Unbind() const;
	// Cleans up VBO on OpenGL's side
	void Delete();
	~UBO();

	// Makes this class non-copyable
	UBO(const UBO&) = delete;
	UBO& operator=(const UBO&) = delete;

private:
	GLuint ID = 0;
	unsigned int blockIndex = 0;
};

#endif