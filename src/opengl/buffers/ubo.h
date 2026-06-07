#ifndef UBO_H
#define UBO_H

#include <glad/glad.h>

#include "opengl/resources/shader.h"

#include <vector>
#include <iostream>

class UBO
{
public:
	// Constructs a VBO. This buffer will not remain bound after execution.
	UBO(const std::vector<float>& data, unsigned int slot);
	void LinkUni(const Shader& shader,const char* uniform) const;
	void Bind() const;
	void Unbind() const;
	void Delete();
	~UBO();

	UBO(const UBO&) = delete;
	UBO& operator=(const UBO&) = delete;

private:
	GLuint ID = 0;
	unsigned int blockIndex = 0;
};

#endif