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
    // Constructor intakes generic vert/ind/uv vector.
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector <Texture>& textures);
    void Draw(
        Shader& shader,
        Viewport& camera,
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)    
    );
    ~Mesh();

    private:
    // OpenGL glints 
    VAO vao; 
    VBO vbo;
    EBO ebo;
    
    // Copy of data that GPU is crunching
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures; 

};

#endif