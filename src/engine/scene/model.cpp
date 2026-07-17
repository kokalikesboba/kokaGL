#include "model.h"

Model::Model(const std::string& modelDir)
{
    ParseGLTF model(modelDir);
}

const std::vector<PNCUVertex> *Model::GetVertices() const
{
    return &vertices;
}

const std::vector<unsigned int> *Model::GetIndices() const
{
    return &indices;
}

const std::vector<unsigned char*>* Model::GetTexData() const
{
    return &textures;
}
