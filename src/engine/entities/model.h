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
    void AddPosition(glm::vec3 position);
    glm::vec3 GetPosition() const;

    void SetEulerRotation(glm::vec3 rotation);
    void AddEulerRotation(glm::vec3 rotation);
    void SetOrientation(glm::quat orientation);
    void Rotate(glm::vec3 rotation);

private:
    std::unique_ptr<Mesh> mesh;

    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::quat orientation = {1.f, 0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f, 1.f, 1.f};

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::string> texPath;
    std::vector<textureType> texTypeIndex;
};
#endif