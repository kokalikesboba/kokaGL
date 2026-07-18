#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

#include "opengl/buffers/ubo.h"
#include "opengl/resources/shader.h"

struct lightUBO {
    glm::vec4 color0        = glm::vec4(0.f);
    glm::vec3 direction0    = glm::vec3(0.f);
    float pad0              = 0;
    glm::vec4 color1        = glm::vec4(0.f);
    glm::vec3 direction1    = glm::vec3(0.f);
    float pad1              = 0;
};

class Light {
public:
    Light();
    void LinkUniformBlock(Shader& shader, GLuint blockindex);
    void UpdateUniformBlock(
        glm::vec4 rgba,
        glm::vec3 direction
    );
    ~Light();
private:
    UBO ubo;
};

#endif