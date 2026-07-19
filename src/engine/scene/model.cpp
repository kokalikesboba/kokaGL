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
const std::vector<ModelRenderData>* Model::GetModelRenderData() const
{
    return &meshData;
}