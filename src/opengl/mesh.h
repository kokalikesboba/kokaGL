#ifndef MESH_H
#define MESH_H

#include "vao.h"
#include "ebo.h"
#include "viewport.h"
#include "texture.h"

#include <string>
#include <vector>

class Mesh {

public:
    Mesh(
        const std::vector<Vertex>& vertices,
        const std::vector<GLuint>& indices,
        const std::vector <Texture>& textures
    );
    void Draw(
        Shader& shader,
        Viewport& viewport,
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)    
    ) const;
    // Destructor
    ~Mesh();

private:
    // OpenGL glints 
    VAO vao;

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;
    
    // Copy of data that GPU is crunching
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures; 

};

#endif