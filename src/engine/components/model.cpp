#include "model.h"

Model::Model(const std::string &modelDir, TexturePool& texturepool)
{

    Parser parsed(modelDir);
    
    for (int i = 0; i < parsed.textureHash.size(); ++i) {
        if ()
    }

    vertices = std::move(parsed.vertices);
    indices = std::move(parsed.indices);

    if (parsed.vertices.size() == 0 ||
        parsed.indices.size() == 0 || 
        parsed.textureData.size() == 0) {

        textures.emplace_back(std::make_shared<Texture>(textureType::BaseColor));
        textures[0]->genRGBATexture(fallbackPixels, 2, 2);

        std::make_unique<Mesh>(kErrorVertices,  kErrorIndices, textures);
    }

    std::make_unique<Mesh>(vertices, indices, textures);
}

void Model::Draw(const Shader &shader) const
{
    mesh->Draw(shader, position, orientation, scale);
}

void Model::SetPosition(glm::vec3 position)
{
    this->position = position;
}

void Model::AddPosition(glm::vec3 position)
{
    this->position += position;
}

glm::vec3 Model::GetPosition() const
{
    return position;
}

void Model::SetEulerRotation(glm::vec3 rotation)
{
    glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    orientation = qYaw * qPitch * qRoll;
}

void Model::AddEulerRotation(glm::vec3 rotation)
{
    glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::quat delta = qYaw * qPitch * qRoll;
    orientation *= delta;
}

void Model::SetOrientation(glm::quat orientation)
{
    this->orientation = orientation;
}

glm::quat Model::GetOrientation() const
{
    return orientation;
}
