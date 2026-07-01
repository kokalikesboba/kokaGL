    #include "mesh.h"

    Mesh::Mesh(
        std::vector<PNCUVertex>& vertices,
        std::vector<GLuint>& indices,
        std::vector <std::shared_ptr<Texture>> textures
    ) :
        textures(std::move(textures)),
        vbo(vertices), 
        ebo(indices)
    {
        indicesCount = indices.size();
        vao.Bind();
        ebo.Bind();
        vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, position));
        vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, normal));
        vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, color));
        vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, uv));
    }

    void Mesh::Draw(
        const Shader& shader,
        const glm::vec3& position,
        const glm::quat& orientation,
        const glm::vec3& scale)
    {
        vao.Bind();
        ebo.Bind();
        shader.Activate();

        // Converts enum to int for shader slots.
        for (auto& tex : textures) {
            tex->Bind(int(tex->getType()));
        }

        glm::mat4 translationMatrix = glm::mat4(1.0f);
        translationMatrix = glm::translate(translationMatrix, position);
        glm::mat4 rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::mat4_cast(orientation);
        glm::mat4  scalingMatrix = glm::mat4(1.0f);
        scalingMatrix = glm::scale(scalingMatrix, scale);
        glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));  

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT,0);
    }

    Mesh::~Mesh()
    {
        // Intentionally left blank.
    }