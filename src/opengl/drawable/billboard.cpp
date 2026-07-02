#include "billboard.h"

Billboard::Billboard (
    Texture* texture)
    :
    texture(texture),
    vbo(squareVerts),
    ebo(squareIndices)
{
    vao.Bind();
    ebo.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, position));
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, normal));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, uv));
}

void Billboard::Draw(
    Shader &shader,
    const glm::vec3 &position,
    const glm::vec2 &scale)
{
    vao.Bind();
    ebo.Bind();
    shader.Activate();
    this->texture->Bind(0);

    glm::mat4 translationMatrix = glm::mat4(1.0f);
    translationMatrix = glm::translate(translationMatrix, position);
    glm::mat4  scalingMatrix = glm::mat4(1.0f);
    scalingMatrix = glm::scale(scalingMatrix, {scale, 1.f});
    glm::mat4 modelMatrix = translationMatrix * scalingMatrix;

    shader.UploadUni("modelMatrix", modelMatrix);

    glDrawElements(GL_TRIANGLES, squareIndices.size(), GL_UNSIGNED_INT,0);
}

Billboard::~Billboard()
{
    // Intentionally left blank.
}
