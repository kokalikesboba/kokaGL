    #include "mesh.h"

    Mesh::Mesh(
        std::vector<Vertex> vertices,
        std::vector<GLuint> indices,
        std::vector <std::shared_ptr<Texture>> textures
    ) : 
        vertices(std::move(vertices)),
        indices(std::move(indices)),
        textures(std::move(textures)),
        // Call the constructors on the member variables of Mesh.
        vbo(this->vertices), 
        ebo(this->indices)
    {
        vao.Bind();
        ebo.Bind();
        vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
        vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
        vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texUV));

        for (int i = 0; i < this->textures.size(); ++i) {
            this->textures[i]->genRGBATexture(nullptr);
        }

    }

    void Mesh::Draw(
        const Shader& shader,
        const glm::vec3& translation,
        const glm::quat& rotation,
        const glm::vec3& scale)
    {
        vao.Bind();
        shader.Activate();

        for (int i = 0; i < textures.size(); ++i) {
            switch (textures[i]->getType()) {
                case textureType::BaseColor: textures[i]->Bind(0); break;
                case textureType::OcclusionRoughnessMetallic: textures[i]->Bind(1); break;
                case textureType::Normal: textures[i]->Bind(2); break;
                case textureType::Emissive: textures[i]->Bind(3); break;
            }
        }

        glm::mat4 translationMatrix = glm::mat4(1.0f);
        translationMatrix = glm::translate(translationMatrix, translation);

        glm::mat4 rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::mat4_cast(rotation);
        
        glm::mat4  scalingMatrix = glm::mat4(1.0f);
        scalingMatrix = glm::scale(scalingMatrix, scale);

        glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));  

        // Draw
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
    }

    Mesh::~Mesh()
    {
        // Intentionally left blank.
    }