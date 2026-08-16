#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

#include <vector>
#include <iostream>

class EBO
{
public:
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