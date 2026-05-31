#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "opengl/drawable/mesh.h"
#include "opengl/format.h"

#include "glad/glad.h"

#include <stdexcept>
#include <iostream>
#include <memory>

class Model
{
public:
    Model(const char* modelDir);
    void Draw(const Shader& shader) const;

    void SetPosition(glm::vec3 position);
    void Translate(glm::vec3 translate);
    void SetOrientation(glm::vec3 rotation);
    void Rotate(glm::vec3 rotation);

private:
    glm::vec3 position;
    glm::quat rotation = glm::quat(1,0,0,0);
    glm::vec3 scale;

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::string> texPath;
    std::vector<textureType> texTypeIndex;

    std::unique_ptr<Mesh> mesh;
};
#endif