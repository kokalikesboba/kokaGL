#ifndef LIGHT_H
#define LIGHT_H

#include "engine/entities/model.h"

class Light {
public: 
    Light(
        glm::vec3 color
    );
    void Draw(const Shader& shader) const;
    void LinkRotation(const Shader& shader, const char* uniform) const;
    void LinkColor(const Shader& shader, const char* uniform) const;

    void SetPosition(glm::vec3 position);
    void Translate(glm::vec3 translate);
    void SetOrientation(glm::vec3 euler);
    void Rotate(glm::vec3 rotation);

private:
    glm::vec3 position;
    glm::quat rotation = glm::quat(1,0,0,0);
    
    glm::vec3 color;
    Model gizmo;
};

#endif