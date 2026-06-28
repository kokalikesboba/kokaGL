#ifndef MODEL_H
#define MODEL_H

#include "opengl/drawable/mesh.h"

#include "engine/runtime/texturepool.h"
#include "engine/runtime/parser.h"

#include <iostream>
#include <memory>

class Model {
public:
    Model(const std::string& modelDir, TexturePool& textureCache);
    void Draw(const Shader& shader) const;

    void SetPosition(glm::vec3 position);
    void AddPosition(glm::vec3 position);
    glm::vec3 GetPosition() const;

    void SetEulerRotation(glm::vec3 rotation);
    void AddEulerRotation(glm::vec3 rotation);
    void SetOrientation(glm::quat orientation);
    glm::quat GetOrientation() const;

private:
    std::unique_ptr<Mesh> mesh = nullptr;

    std::vector<PNCUVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::quat orientation  = {1.f, 0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f, 1.f, 1.f};
};
 
#endif