#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include"vbo.h"

#include <iostream>

class VAO
{
public:
	// Constructor that generates a VAO ID
	VAO();
	// Links a VBO to the VAO using a certain layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
	// Deconstructor
	~VAO();
private:
	// ID reference for the Vertex Array Object
	GLuint ID;
};
#endif