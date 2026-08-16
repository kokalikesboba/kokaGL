    #include "mesh.h"

    using RenderFormat::PNCUVertex;

    Mesh::Mesh(
        const std::vector<RenderFormat::PNCUVertex>& vertices,
        const std::vector<GLuint>& indices
    ) :
        vbo(std::move(vertices)), 
        ebo(std::move(indices))
    {
        indicesCount = indices.size();
        vao.Bind();
        ebo.Bind();
        vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, position));
        vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, normal));
        vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, color));
        vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(PNCUVertex), (void*)offsetof(PNCUVertex, uv));
    }

    void Mesh::Draw(Shader &shader, const glm::mat4 &modelMatrix)
    {
        vao.Bind();
        ebo.Bind();
        shader.Activate();

        shader.UploadUni("modelMatrix", modelMatrix);

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT,0);
    }

    Mesh::~Mesh()
    {
    }