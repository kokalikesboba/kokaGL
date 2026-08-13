#ifndef MESH_H
#define MESH_H

#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "opengl/buffers/vao.h"
#include "opengl/buffers/ebo.h"
#include "opengl/resources/shader.h"
#include "opengl/resources/texture.h"

#include "formats/renderformat.hpp"

#include <memory>

class Mesh {
public:
    Mesh(
        const std::vector<RenderFormat::PNUVertex>& vertices,
        const std::vector<unsigned int>& indices
    );
    void Draw(
        Shader& shader,
        const glm::mat4 &modelMatrix
    );
    ~Mesh();
private:
    VAO vao; 
    VBO vbo;
    EBO ebo;
    unsigned int indicesCount = 0;
};

#endif