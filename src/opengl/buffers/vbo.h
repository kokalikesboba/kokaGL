#ifndef VBO_H
#define VBO_H

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "opengl/format.h"

#include <vector>
#include <iostream>

class VBO
{
public:
	VBO();
	
	VBO(const std::vector <Vertex>& vertices);
	void Bind() const;
	void Unbind() const;
	void Delete();
	~VBO();

	// Makes this class non-copyable
	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;

private:
	GLuint ID = 0;
};

#endif