#ifndef LIGHT_H
#define LIGHT_H

#include "math/transform.h"
#include "engine/runtime/texturepool.h"
#include "engine/scene/model.h"

#include <string>

class Light : public Transform {
public: 
    Light(glm::vec3 color);
    void Draw(const Shader& shader) const;
    glm::vec3 getColor();

private:
    glm::vec3 color = {1.f, 1.f, 1.f};
};

#endif