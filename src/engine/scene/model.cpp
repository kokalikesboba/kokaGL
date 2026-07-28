#include "model.h"

Model::Model(const std::string& modelDir)
{
    ParseGLTF parsed(modelDir);
    size_t n = parsed.vertices.size();
    data.resize(n);
    for (size_t i = 0; i < n; ++i) {
        data[i].vertices = std::move(parsed.vertices[i]);
        data[i].indices  = std::move(parsed.indices[i]);
        if (i < parsed.texData.size())
            data[i].texData = std::move(parsed.texData[i]);
        data[i].position = {0.f, 0.f, 0.f};
        data[i].orientation = glm::quat(1.f, 0.f, 0.f, 0.f);  // w first!
        data[i].scale = {1.f, 1.f, 1.f};
    }
    meshCount = data.size();
}
const std::vector<RenderData>* Model::GetRenderData() const
{
    return &data;
}

void Model::DeleteRenderData()
{
    data.clear();
}

const int Model::GetMeshCount() const
{
    return meshCount;
}
