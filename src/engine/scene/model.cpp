#include "model.h"

Model::Model(const std::string& modelDir)
{
    ParseGLTF model(modelDir);
    data = std::move(model.data);
}
const std::vector<MeshRenderData>* Model::GetRenderData() const
{
    return &data;
}

void Model::DeleteRenderData()
{
    data.clear();
}