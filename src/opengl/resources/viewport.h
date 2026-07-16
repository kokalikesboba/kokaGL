#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "opengl/buffers/ubo.h"
#include "opengl/resources/shader.h"

struct viewportUBO {
	glm::mat4 matrix;
	glm::mat4 orientation;
	glm::vec3 pos;
	float pad0;
};

class Viewport
{
public:
	Viewport();
    void Resize(int width, int height);
    void LinkUniformBlock(Shader& shader, GLuint blockIndex);
    void UpdateUniformBlock(
        glm::mat4 matrix,
        glm::mat4 orientation,
        glm::vec3 pos
    );
    ~Viewport();
private:
    int prevWidth = 0;
    int prevHeight = 0;
    UBO ubo;
};

#endif