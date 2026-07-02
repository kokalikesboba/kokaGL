#ifndef MODEL_H
#define MODEL_H

#include "math/transform.h"
#include "opengl/drawable/mesh.h"
#include "engine/runtime/texturepool.h"
#include "engine/parsers/gltf.h"

#include <iostream>
#include <memory>

class Model : public Transform {
public:
    Model(const std::string& modelDir, TexturePool& textureCache);
    void Draw(Shader& shader) const;
private:
    std::unique_ptr<Mesh> mesh = nullptr;

    std::vector<PNCUVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    // TODO: might be worth adding this to math
    glm::vec3 scale = {1.f, 1.f, 1.f};
};
 
#endif