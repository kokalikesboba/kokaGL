#include "model.h"

Model::Model(const std::string& modelDir)
{
    ParseGLTF parsed(modelDir);
    meshData.push_back({
        std::move(parsed.vertices),
        std::move(parsed.indices),
        std::move(parsed.texData)
    });
}
const std::vector<RenderFormat::PNCUVertex>* Model::GetVertices() const
{
    return &meshData[0].vertices;
}

const std::vector<unsigned int>* Model::GetIndices() const
{
    return &meshData[0].indices;
}

const std::vector<RenderFormat::TextureData>* Model::GetTexInfo() const
{
    return &meshData[0].texInfo;
}