    #include "mesh.h"

    using RenderFormat::PNUVertex;

    Mesh::Mesh(
        const std::vector<RenderFormat::PNUVertex>& vertices,
        const std::vector<GLuint>& indices
    ) :
        vbo(std::move(vertices)), 
        ebo(std::move(indices))
    {
        indicesCount = indices.size();
        vao.Bind();
        ebo.Bind();
        vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, position));
        vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, normal));
        vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(PNUVertex), (void*)offsetof(PNUVertex, uv));
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