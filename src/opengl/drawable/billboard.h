#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <opengl/buffers/vao.h>
#include <opengl/buffers/ebo.h>
#include <opengl/resources/texture.h>
#include <opengl/resources/shader.h>

#include "glm/gtc/quaternion.hpp"
#include "glm/mat3x3.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "formats/renderformat.hpp"

class Billboard {
public:
    // Constructor Intakes raw image bytes and uploads it to the GPU
    Billboard();
    void Draw(
        Shader& shader,
        const glm::vec3& position = {0.f, 0.f, 0.f},
        const glm::vec2& scale = {1.f, 1.f}
    );
    ~Billboard();
    Billboard(const Billboard&) = delete;
    Billboard& operator=(const Billboard&) = delete;
private:
    VAO vao; 
    VBO vbo;
    EBO ebo;
};

#endif