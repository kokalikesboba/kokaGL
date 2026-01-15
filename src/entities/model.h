#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "opengl/renderer/mesh.h"
#include "parsers/gltfAssimp.h"

class Model
{
public:
    Model();
    void Draw(const Shader& shader) const;

private:
	std::vector<Mesh> mesh;
};
#endif