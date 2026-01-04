#ifndef MESH_H
#define MESH_H

#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "texture.h"

#include <string>
#include <vector>

class Mesh {
    public:
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures; 

    VAO vao;
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector <Texture>& textures);

    void Draw(Shader& shader, Camera& camera);

};

#endif