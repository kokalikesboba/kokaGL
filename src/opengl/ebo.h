#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>

#include <iostream>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	EBO();
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(std::vector<GLuint>& indices);
	// Binds the EBO
	void Bind();
	// Buffers data into EBO
	void Buffer(std::vector<GLuint>& indices);
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
	// Deconstructor
	~EBO();
};

#endif