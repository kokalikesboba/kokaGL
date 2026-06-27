#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <opengl/buffers/vao.h>
#include <opengl/buffers/ebo.h>
#include <opengl/resources/texture.h>

#include "glm/gtc/quaternion.hpp"

#include <vector>
/*
std::vector<BillboardVertex> bbVertices = {
    // position                  normal             uv
    {{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // top right
    {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // top left
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // bottom left
    {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // bottom right
};

std::vector<unsigned int> bbIndices = {
    0, 1, 2,
    2, 3, 0
};

class Billboard {
public:
    Billboard(
        std::vector<unsigned char>& texture
    );
    void Draw(
        const Shader& shader,
        const glm::vec3& position = {0.f, 0.f, 0.f},
        const glm::quat& orientation = {1.f, 0.f, 0.f, 0.f},
        const glm::vec3& scale = {1.f, 1.f, 1.f}
    );
    ~Billboard();
private:
    VAO vao; 
    VBO vbo;
    EBO ebo;
    // Texture won't hook into pool for now.
    Texture texture; 
};
*/

#endif