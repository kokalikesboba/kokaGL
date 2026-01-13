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
        const Shader& shader,
        std::vector<Vertex> vertices,
        std::vector<GLuint> indices,
        std::vector<Texture> textures
    );
    void Draw(
        const Shader& shader,
        const Viewport& viewport,
        const glm::vec3& translation = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)    
    ) const;
    // Destructor
    ~Mesh();

private: 
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures;
    VAO vao; 
    VBO vbo;
    EBO ebo;
    int numDiffuse = 0;
    int numSpecular = 0;

};

#endif