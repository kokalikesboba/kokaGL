#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(const std::string &modelDir)
{
    /* Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( modelDir,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
    }
    */

    // Pretending I have a placeholder missing Model
}

void Model::Draw(const Shader &shader) const
{
    for (int i = 0; mesh.size(); ++i) {
        mesh[i]->Draw(shader, position, orientation, scale);
    }
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
