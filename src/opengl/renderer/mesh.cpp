#include "mesh.h"

std::string getTextureTypePrefix(textureType type) {
    switch (type) {
        case textureType::Diffuse: return "diffuse";
        case textureType::Specular: return "specular";
        default: return "unknown";
    }
}

Mesh::Mesh(
    std::vector<Vertex> vertices,
    std::vector<GLuint> indices,
    std::vector<Texture> textures
) : 
    vertices(std::move(vertices)),
    indices(std::move(indices)),
    textures(std::move(textures)),
    // Call the constructors on the member variables of Mesh.
    vbo(this->vertices), 
    ebo(this->indices)
{
    shaderID = 0;
    vao.Bind();
    ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texUV));
    vao.Unbind();
	ebo.Unbind();   

    for (int i = 0; i < this->textures.size(); ++i) {
        this->textures[i].genTexture();
    }

}

void Mesh::Draw(
    const Shader& shader,
    const Viewport& viewport,
    const glm::vec3& translation,
    const glm::quat& rotation,
    const glm::vec3& scale)
{   
    vao.Bind();
    shader.Activate();

    // Uploads texture uniform once, if draw is called with new shader, reupload.
    if (shaderID != shader.getID()) {
        shaderID = shader.getID();
        numDiffuse = 0;
        numSpecular = 0;
        for (int i = 0; i < textures.size(); ++i) {
            if (textures[i].getType() == textureType::Diffuse) {
                textures[i].linkUni(
                    shader,
                    (getTextureTypePrefix(textures[i].getType()) + std::to_string(numDiffuse)).c_str()
                    
                );
                numDiffuse++;
            } else if (textures[i].getType() == textureType::Specular) {
                
                textures[i].linkUni(
                    shader,
                    (getTextureTypePrefix(textures[i].getType()) + std::to_string(numSpecular)).c_str()
                    
                );
                numSpecular++;
            }
        }
        std::cout 
        << "Mesh has\n"  
        << "   " << numDiffuse << " diffuse\n" 
        << "   " << numSpecular << " specular\n";
    }

    // Upload camera position as a uniform for lighting
    // Uploades the texture uniform for fragment shaders. 
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