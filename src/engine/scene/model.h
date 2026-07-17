#ifndef MODEL_H
#define MODEL_H

#include "math/transform.h"
#include "engine/parsers/gltf.h"

class Model : public Transform {
public:
    Model(const std::string& modelDir);
    const std::vector<PNCUVertex>* GetVertices() const;
    const std::vector<unsigned int>* GetIndices() const;
    const std::vector<unsigned char*>* GetTexData() const;
private:
    std::vector<PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned char*> textures;
};

#endif