#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <opengl/buffers/vao.h>
#include <opengl/buffers/ebo.h>
#include <opengl/resources/texture.h>

#include "glm/gtc/quaternion.hpp"
#include "glm/mat3x3.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

class Billboard {
public:
    // Constructor Intakes raw image bytes and uploads it to the GPU
    Billboard(
        std::vector<PNUVertex>& vertices,
        std::vector<unsigned int>& indices,
        std::vector<unsigned char>& texture,
        int width,
        int height
    );
    void Draw(
        const Shader& shader,
        const glm::vec3& position = {0.f, 0.f, 0.f},
        const glm::vec2& scale = {1.f, 1.f}
    );
    ~Billboard();
private:
    VAO vao; 
    VBO vbo;
    EBO ebo;

    std::vector<PNUVertex> vertices;
    std::vector<unsigned int> indices;
    // Texture won't hook into pool for now.
    Texture texture; 

};

#endif