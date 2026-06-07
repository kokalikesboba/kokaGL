#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "vbo.h"

#include <iostream>

class VAO {
	public:
		// Construct a VAO.
		VAO();
		// Links a VBO to a VAO. 
		void LinkAttrib(
			const VBO& VBO,
			const GLuint& layout,
			const GLuint& numComponents,
			const GLenum& type,
			const GLsizeiptr& stride,
			const void* offset) const;
		void Bind() const;
		void Unbind() const;
		void Delete();
		~VAO();

		// Makes this class non-copyable
		VAO(const VBO&) = delete;
		VAO& operator=(const VBO&) = delete;

	private:
		// ID reference for the Vertex Array Object
		GLuint ID = 0;
};
#endif