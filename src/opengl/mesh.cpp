#include "mesh.h"

std::string getTextureTypePrefix(textureType type) {
    switch (type) {
        case textureType::Diffuse: return "diffuse";
        case textureType::Specular: return "specular";
        default: return "unknown";
    }
}

Mesh::Mesh(
    const std::vector<Vertex> &vertices,
    const std::vector<GLuint> &indices,
    const std::vector<Texture> &textures
) : vbo(vertices), ebo(indices)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    vao.Bind();
    ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texUV));
    vao.Unbind();
	ebo.Unbind();   
}

/*
void Mesh::bufferTexture(std::vector<Texture> &textures, const Shader& shader)
{
    numDiffuse = 0;
    numSpecular = 0;
    for (unsigned int i = 0;  i < textures.size(); i++) {
        std::string num;
        textureType type = textures[i].type;
        if (type == textureType::Diffuse) {
            num = std::to_string(numDiffuse++);
        } else if (type == textureType::Specular) {
            num = std::to_string(numSpecular++);
        }
        textures[i].linkUni(shader, (getTextureTypePrefix(type) + num).c_str(), i);
        textures[i].Bind();
    }
}
*/

void Mesh::Draw(
    const Shader &shader,
    const Viewport &viewport,
    const glm::vec3& translation,
    const glm::quat& rotation,
    const glm::vec3& scale) const
{   
    vao.Bind();
    shader.Activate();
    // Upload camera position as a uniform to the shader program.
    glUniform3f(
        glGetUniformLocation(shader.getID(), "camPos"),
        viewport.Position.x,
        viewport.Position.y,
        viewport.Position.z
    );
    viewport.linkMatrix(shader, "camMatrix");

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4  sca = glm::mat4(1.0f);

    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
   
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);

}

Mesh::~Mesh()
{
    // Should be empty!
}