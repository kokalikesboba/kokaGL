#include "viewport.h"

Viewport::Viewport() : ubo(sizeof(viewportUBO), 0)
{
}

// Resizes viewport only if the window size has changed 
void Viewport::Resize(int width, int height)
{
    if ((prevWidth != width) || (prevHeight != height)) {
        prevWidth = width;
        prevHeight = height;
        glViewport(0,0, width, height);
    }
}

void Viewport::LinkUniformBlock(Shader &shader, GLuint blockIndex)
{
    ubo.LinkBlock(shader, blockIndex);
}

void Viewport::UpdateUniformBlock(glm::mat4 matrix, glm::mat4 orientation, glm::vec3 pos)
{
    ubo.Update(
        viewportUBO(
            {matrix, orientation, pos, float(0.f)}
        )
    );
}

Viewport::~Viewport()
{
}
