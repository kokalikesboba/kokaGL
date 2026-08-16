#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "opengl/buffers/ubo.h"
#include "opengl/resources/shader.h"

class Viewport
{
public:
	Viewport();
    void Resize(int width, int height);
    ~Viewport();
private:
    int prevWidth = 0;
    int prevHeight = 0;
};

#endif