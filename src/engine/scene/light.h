#ifndef LIGHT_H
#define LIGHT_H

#include "engine/runtime/texturepool.h"
#include "engine/components/model.h"

#include <string>

class Light {
public: 
    Light(glm::vec3 color);
    void Draw(const Shader& shader) const;
    void LinkRotation(const Shader& shader, const char* uniform) const;
    void LinkColor(const Shader& shader, const char* uniform) const;

    void SetPosition(glm::vec3 position);
    void Translate(glm::vec3 translate);
    void SetOrientation(glm::vec3 euler);
    void Rotate(glm::vec3 rotation);

private:
    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::quat rotation = {1.f, 0.f, 0.f, 0.f};
    glm::vec3 color = {1.f, 1.f, 1.f};
};

#endif