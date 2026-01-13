#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include"vbo.h"

#include <iostream>

class VAO
{
public:
	// Construct a VAO.
	VAO();
	// Links a VBO to a VAO. 
	void LinkAttrib(const VBO& VBO,
		const GLuint& layout,
		const GLuint& numComponents,
		const GLenum& type,
		const GLsizeiptr& stride,
		const void* offset) const;
	// Binds the VAO
	void Bind() const;
	// Unbinds the VAO
	void Unbind() const;
	// Cleans up VAO on OpenGL's side
	void Delete();
	// Deconstructor
	~VAO();
private:
	// ID reference for the Vertex Array Object
	GLuint ID = 0;
};
#endif