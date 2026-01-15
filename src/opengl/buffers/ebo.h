#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

#include <vector>
#include <iostream>

class EBO
{
public:
	// Creates and uploads an element buffer (index buffer).
	// Note: GL_ELEMENT_ARRAY_BUFFER binding is stored in the currently bound VAO,
	// so do NOT unbind the EBO while configuring a VAO you want to keep indexed.
	EBO(const std::vector<GLuint>& indices);
	// Binds the EBO
	void Bind() const;
	// Unbinds the EBO
	void Unbind() const;
	// Deletes the EBO
	void Delete();
	// Deconstructor
	~EBO();

	// Prevents copying
	EBO(const EBO&) = delete;
	EBO& operator=(const EBO&) = delete;
private:
	GLuint ID;
};

#endif