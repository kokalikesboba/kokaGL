#ifndef MODEL_H
#define MODEL_H

#include "math/transform.h"
#include "engine/parsers/gltf.h"

struct ModelRenderData {
    std::vector<RenderFormat::PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<RenderFormat::TextureData> texData;
};

class Model : public Transform {
public:
    Model(const std::string& modelDir);
    const std::vector<ModelRenderData>* GetModelRenderData() const;
private:
    std::vector<ModelRenderData> meshData;
};

#endif