#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

#include <vector>
#include <iostream>

class EBO
{
public:
	// Note: GL_ELEMENT_ARRAY_BUFFER binding is stored in the currently bound VAO,
	// so do NOT unbind the EBO while configuring a VAO you want to keep indexed.
	EBO(const std::vector<GLuint>& indices);
	void Bind() const;
	void Unbind() const;
	void Delete();
	~EBO();

	EBO(const EBO&) = delete;
	EBO& operator=(const EBO&) = delete;
private:
	GLuint ID;
};

#endif