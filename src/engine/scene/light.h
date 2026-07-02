#ifndef LIGHT_H
#define LIGHT_H

#include "engine/runtime/texturepool.h"
#include "engine/scene/model.h"

#include <string>

class Light {
public: 
    Light(glm::vec3 color);
    void Draw(const Shader& shader) const;

    void SetPosition(glm::vec3 position);
    void Translate(glm::vec3 translate);
    void SetOrientation(glm::vec3 euler);
    void Rotate(glm::vec3 rotation);

    glm::vec3 getColor();
    glm::vec3 getOrientation();

private:
    glm::vec3 color = {1.f, 1.f, 1.f};

    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::quat orientation = {1.f, 0.f, 0.f, 0.f};
};

#endif