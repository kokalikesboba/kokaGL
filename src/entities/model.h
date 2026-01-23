#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "opengl/renderer/mesh.h"
#include "parsers/gltfAssimp.h"

#include <memory>

class Model
{
public:
    Model(const char* modelDir);
    void Draw(const Shader& shader) const;

private:
    std::unique_ptr<Mesh> mesh;
};
#endif