#include "model.h"

Model::Model(const std::string &modelDir, TexturePool& textureCache)
{

    Parser parsed(modelDir);

    for (int i = 0; i < parsed.texHash.size(); ++i) {
        if (textureCache.isCachedAndAlive(parsed.texHash[i])) {
            textures.push_back(textureCache.Get(parsed.texHash[i]));
        } else {
            textures.push_back(
                textureCache.Add(
                    parsed.texHash[i],
                    parsed.texType[i],
                    parsed.texData[i],
                    parsed.texWidth[i],
                    parsed.texHeight[i]
                )   
            );
        }
    }

    vertices = std::move(parsed.vertices);
    indices = std::move(parsed.indices);

    mesh = std::make_unique<Mesh>(vertices, indices, textures);
}

void Model::Draw(Shader &shader) const
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
