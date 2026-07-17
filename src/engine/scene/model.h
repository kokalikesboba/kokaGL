#ifndef MODEL_H
#define MODEL_H

#include "math/transform.h"
#include "engine/parsers/gltf.h"

class Model : public Transform {
public:
    Model(const std::string& modelDir);
    const std::vector<RenderFormat::PNCUVertex>* GetVertices() const;
    const std::vector<unsigned int>* GetIndices() const;
    const std::vector<RenderFormat::TextureInfo>* GetTexInfo() const;
    const std::vector<std::vector<unsigned char>>* GetTexData() const;
private:
    std::vector<RenderFormat::PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<RenderFormat::TextureInfo> texInfo;
    std::vector<std::vector<unsigned char>> texData;
};

#endif