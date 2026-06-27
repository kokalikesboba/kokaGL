#include "billboard.h"

Billboard::Billboard(std::vector<unsigned char>& texture, int width, int height) :
vbo(bbVertices),
ebo(bbIndices),
texture(TextureType::BaseColor)
{
    this->texture.genRGBATexture(texture.data(), width, height);
    vao.Bind();
    ebo.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, position));
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, normal));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, uv));
}

void Billboard::Draw(
    const Shader &shader,
    const glm::vec3 &position,
    const glm::vec3 &scale)
{
    vao.Bind();
    ebo.Bind();
    shader.Activate();
    this->texture.Bind(0);

    glm::mat4 translationMatrix = glm::mat4(1.0f);
    translationMatrix = glm::translate(translationMatrix, position);
    glm::mat4  scalingMatrix = glm::mat4(1.0f);
    scalingMatrix = glm::scale(scalingMatrix, scale);
    glm::mat4 modelMatrix = translationMatrix * scalingMatrix;

    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));  

    glDrawElements(GL_TRIANGLES, bbIndices.size(), GL_UNSIGNED_INT,0);
}
