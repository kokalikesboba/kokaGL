#ifndef MODEL_H
#define MODEL_H

#include "math/transform.h"
#include "engine/parsers/gltf.h"

class Model : public Transform {
public:
    Model(const std::string& modelDir);
    const std::vector<MeshRenderData>* GetRenderData() const;

    void DeleteRenderData();
    
private:
    std::vector<MeshRenderData> data;
};

#endif