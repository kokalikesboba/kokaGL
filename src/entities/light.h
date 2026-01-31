#ifndef LIGHT_H
#define LIGHT_H

#include "entities/model.h"

class Light {
public: 
    Light(
        glm::vec3 color
    );
    const void DrawGizmo(const Shader& shader);
    Model gizmo;
    glm::vec3 color;
private:
    
};

#endif