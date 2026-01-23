#include "model.h"

Model::Model(const char* modelDir) {
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
    mesh->Draw(shader);
}
