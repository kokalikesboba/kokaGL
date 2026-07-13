#include "model.h"

Model::Model(const std::string &modelDir, TexturePool& textureCache)
{

    ParseGLTF parsed(modelDir);

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