#include "model.h"

Model::Model(const char* modelDir) {
    
    position = {0.f, 0.f, 0.f};
    scale = {1.f, 1.f, 1.f};

    returnedData parsed = loadModelData(modelDir);
    std::vector<Texture> textures;

    if (parsed.texTypeIndex.empty()) {
        // Create EXACTLY one texture with default settings (Missing Texture)
        textures.emplace_back(textureType::Diffuse, 0); 
    } else {
        textures.reserve(parsed.texTypeIndex.size());
        for (unsigned int i = 0; i < parsed.texTypeIndex.size(); ++i) {
            textures.emplace_back(parsed.texTypeIndex[i], i);
            
            std::string fullPath = std::string(modelDir) + "/" + parsed.texPath[i];
            textures[i].stbLoad(fullPath); 
        }
    }

    mesh = std::make_unique<Mesh>(
        std::move(parsed.vertices),
        std::move(parsed.indices),
        std::move(textures)
    );
}

void Model::Draw(const Shader &shader) const
{
    mesh->Draw(shader, position, rotation, scale);
}

void Model::SetPosition(glm::vec3 position)
{
    this->position = position;
}

void Model::Translate(glm::vec3 translate)
{
    this->position += translate;
}

void Model::SetOrientation(glm::vec3 rotation)
{
    this->rotation = rotation;
}

void Model::Rotate(glm::vec3 delta) {
    glm::quat rotX = glm::angleAxis(delta.x, glm::vec3(1,0,0));
    glm::quat rotY = glm::angleAxis(delta.y, glm::vec3(0,1,0));
    rotation = rotY * rotX * rotation;
}