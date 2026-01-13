#ifndef VBO_H
#define VBO_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

#include <iostream>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	// Constructs a VBO. This buffer will not remain bound after execution.
	VBO(const std::vector <Vertex>& vertices);
	// Binds the VBO
	void Bind() const;
	// Unbinds the VBO
	void Unbind() const;
	// Cleans up VBO on OpenGL's side
	void Delete();
	~VBO();

	// Makes this class non-copyable
	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;

private:
	GLuint ID = 0;
};

#endif