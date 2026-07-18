#include "light.h"

Light::Light() : ubo(sizeof(lightUBO), 1)
{
}

void Light::LinkUniformBlock(Shader &shader, GLuint blockindex)
{
    ubo.LinkBlock(shader, blockindex);
}

void Light::UpdateUniformBlock(glm::vec4 rgba, glm::vec3 direction)
{
    ubo.Update(
        lightUBO(
            {rgba, direction}
        )
    );
}

Light::~Light()
{
}
