#include "model.h"

Model::Model(const std::string& modelDir)
{
    ParseGLTF parsed(modelDir);
    vertices = std::move(parsed.vertices);
    indices = std::move(parsed.indices);
    texInfo = std::move(parsed.texInfo);
    texData = std::move(parsed.texData);
}

const std::vector<RenderFormat::PNCUVertex>* Model::GetVertices() const
{
    return &vertices;
}

const std::vector<unsigned int>* Model::GetIndices() const
{
    return &indices;
}

const std::vector<RenderFormat::TextureInfo>* Model::GetTexInfo() const
{
    return &texInfo;
}

const std::vector<std::vector<unsigned char>>* Model::GetTexData() const
{
    return &texData;
}
