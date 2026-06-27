#ifndef MESH_H
#define MESH_H

#include "opengl/buffers/vao.h"
#include "opengl/buffers/ebo.h"
#include "opengl/resources/texture.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <vector>
#include <memory>

class Mesh {
public:
    Mesh(
        std::vector<PNCUVertex> vertices,
        std::vector<unsigned int> indices,
        std::vector <std::shared_ptr<Texture>> textures
    );
    void Draw(
        const Shader& shader,
        const glm::vec3& position = {0.f, 0.f, 0.f},
        const glm::quat& orientation = {1.f, 0.f, 0.f, 0.f},
        const glm::vec3& scale = {1.f, 1.f, 1.f}
    );
    ~Mesh();
private: 
    std::vector <PNCUVertex> vertices;
    std::vector <GLuint> indices;
    std::vector <std::shared_ptr<Texture>> textures;

    VAO vao; 
    VBO vbo;
    EBO ebo;

};

#endif