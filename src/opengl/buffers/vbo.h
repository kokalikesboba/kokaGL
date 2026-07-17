#ifndef VBO_H
#define VBO_H

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "engine/formats/rendererformat.hpp"

#include <vector>
#include <iostream>

class VBO
{
public:
	VBO();
	VBO(const std::vector<RenderFormat::PNCUVertex>& vertices);
	VBO(const std::vector<RenderFormat::PNUVertex>& vertices);
	void Bind() const;
	void Unbind() const;
	void Delete();
	~VBO();
	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;

private:
	GLuint ID = 0;
};

#endif