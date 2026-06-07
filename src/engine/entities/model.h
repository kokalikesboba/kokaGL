#ifndef MODEL_H
#define MODEL_H

#include "opengl/drawable/mesh.h"
#include "opengl/format.h"

#include "glad/glad.h"

#include <stdexcept>
#include <iostream>
#include <memory>

class Model
{
public:
    Model(const std::string& modelDir);
    void Draw(const Shader& shader) const;

    void SetPosition(glm::vec3 position);
    void AddPosition(glm::vec3 position);
    glm::vec3 GetPosition() const;

    void SetEulerRotation(glm::vec3 rotation);
    void AddEulerRotation(glm::vec3 rotation);
    void SetOrientation(glm::quat orientation);
    glm::quat GetOrientation() const;

private:
    std::vector<std::unique_ptr<Mesh>> mesh;

    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::quat orientation = {1.f, 0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f, 1.f, 1.f};

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};
 
#endif