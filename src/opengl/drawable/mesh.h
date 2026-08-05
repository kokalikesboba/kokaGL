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
        const std::vector<RenderFormat::PNCUVertex>& vertices,
        const std::vector<unsigned int>& indices
    );
    void Draw(
        Shader& shader,
        const glm::vec3& position = {0.f, 0.f, 0.f},
        const glm::quat& orientation = {1.f, 0.f, 0.f, 0.f},
        const glm::vec3& scale = {1.f, 1.f, 1.f}
    ); 
    ~Mesh();
private:
    VAO vao; 
    VBO vbo;
    EBO ebo;
    unsigned int indicesCount = 0;
};

#endif