#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static const std::vector<Vertex> kErrorVertices = {
    // position              // normal           // color (magenta)    // uv
    // Front
    {{ 0.5f,  0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f,  0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f, -0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{ 0.5f, -0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    // Back
    {{ 0.5f,  0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f,  0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f, -0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    {{ 0.5f, -0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    // Left
    {{-0.5f,  0.5f,  0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f,  0.5f, -0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f, -0.5f, -0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{-0.5f, -0.5f,  0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    // Right
    {{ 0.5f,  0.5f,  0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{ 0.5f,  0.5f, -0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{ 0.5f, -0.5f, -0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    {{ 0.5f, -0.5f,  0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    // Top
    {{ 0.5f,  0.5f, -0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f,  0.5f, -0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f,  0.5f,  0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{ 0.5f,  0.5f,  0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    // Bottom
    {{ 0.5f, -0.5f, -0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    {{-0.5f, -0.5f, -0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{-0.5f, -0.5f,  0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{ 0.5f, -0.5f,  0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
};

static const std::vector<GLuint> kErrorIndices = {
    0,  1,  2,   0,  2,  3,  // front
    4,  6,  5,   4,  7,  6,  // back
    8,  9,  10,  8,  10, 11, // left
    12, 14, 13,  12, 15, 14, // right
    16, 17, 18,  16, 18, 19, // top
    20, 22, 21,  20, 23, 22, // bottom
};

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

    std::vector<Texture> texturePool;
    texturePool.emplace_back(textureType::BaseColor,0);
    // If model size is zero, emplace back one mesh with the placeholder vertices, indices and ONE empty texture.
    if (mesh.empty()) {
        mesh.emplace_back(std::make_unique<Mesh>(kErrorVertices,  kErrorIndices, texturePool));
    }
}

void Model::Draw(const Shader &shader) const
{
    for (int i = 0; i < mesh.size(); ++i) {
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
