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
	// Empty constructor
	VBO();
	// Contstuctor with parameters
	VBO(std::vector <Vertex> vertices);
	// Binds the VBO
	void Bind();
	// Buffers data into existing array 
	void Buffer(std::vector<Vertex> vertices);
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
	~VBO();
private:
	GLuint ID;
};

#endif