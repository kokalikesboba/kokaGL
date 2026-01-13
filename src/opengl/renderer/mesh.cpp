#include "mesh.h"

std::string getTextureTypePrefix(textureType type) {
    switch (type) {
        case textureType::Diffuse: return "diffuse";
        case textureType::Specular: return "specular";
        default: return "unknown";
    }
}

Mesh::Mesh(
    const Shader& shader,
    std::vector<Vertex> vertices,
    std::vector<GLuint> indices,
    std::vector<Texture> textures
) : 
    /*
    These constructor parameters (vertices, indices, textures) are passed
    by VALUE into the Mesh constructor. That means this constructor already
    owns its own local copies of the data, independent of the caller.

    At the call site:
        - lvalues are copied into these parameters
        - rvalues (or std::move'd lvalues) are moved into these parameters

    Inside the constructor, we now want Mesh to become the final owner of
    that data. To do that efficiently, we MOVE the parameter objects into
    the Mesh member variables instead of copying them again.

    std::move DOES NOT move data by itself.
    It simply casts the parameter to an rvalue, which allows the std::vector
    move constructor to run. The move constructor then "steals" the internal
    buffer (pointer, size, capacity) instead of copying all elements.

    After std::move:
        - Mesh member variables own the data
        - The parameter objects are left in a valid but unspecified state
        - The parameters will be destroyed immediately after construction,
          so it is safe to steal from them

    This pattern ("pass by value, then std::move into members") cleanly
    expresses ownership transfer while avoiding unnecessary copies.
    */
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
    vao.Unbind();
	ebo.Unbind();   

    shader.Activate();
    // Uploades the texture uniform for fragment shaders. 
    for (int i = 0; i < this->textures.size(); ++i) {
        this->textures[i].genTexture();
        if (this->textures[i].getType() == textureType::Diffuse) {
            
            this->textures[i].linkUni(
                shader,
                (getTextureTypePrefix(this->textures[i].getType()) + std::to_string(numDiffuse)).c_str()
            );
            numDiffuse++;

        } else if (this->textures[i].getType() == textureType::Specular) {
            
            this->textures[i].linkUni(
                shader,
                (getTextureTypePrefix(this->textures[i].getType()) + std::to_string(numSpecular)).c_str()
            );
            numSpecular++;
        }
    }
    
    std::cout 
    << "Mesh has\n"  
    << "   " << numDiffuse << " diffuse\n" 
    << "   " << numSpecular << " specular\n";
}

void Mesh::Draw(
    const Shader& shader,
    const Viewport& viewport,
    const glm::vec3& translation,
    const glm::quat& rotation,
    const glm::vec3& scale) const
{   
    vao.Bind();
    shader.Activate();
    // Upload camera position as a uniform for lighting
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

    for (int i = 0; i < textures.size(); ++i) {
        textures[i].Bind();
    }

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
    vao.Unbind();
}

Mesh::~Mesh()
{
    // Should be empty!
}