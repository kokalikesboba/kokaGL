#ifndef MODEL_H
#define MODEL_H

#include "math/transform.h"
#include "engine/parsers/gltf.h"

struct RenderData {
    std::vector<RenderFormat::PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<RenderFormat::TextureData> texData;
    glm::vec3 position;
    glm::quat orientation;
    glm::vec3 scale;
};

class Model : public Transform {
public:
    Model(const std::string& modelDir);
    const std::vector<RenderData>* GetRenderData() const;
    void DeleteRenderData();
    
    const int GetMeshCount() const;
private:
    std::vector<RenderData> data;
    int meshCount;
};

#endif