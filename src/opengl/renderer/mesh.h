#ifndef MESH_H
#define MESH_H

#include <opengl/buffers/vao.h>
#include "opengl/buffers/ebo.h"
#include "opengl/pipeline/texture.h"
#include "opengl/renderer/viewport.h"

#include <string>
#include <vector>

class Mesh {

public:
    // Mesh constructor, must use std::move()
    Mesh(
        std::vector<Vertex> vertices,
        std::vector<GLuint> indices,
        std::vector<Texture> textures
    );
    // 
    void Draw(
        const Shader& shader,
        const Viewport& viewport,
        const glm::vec3& translation = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)    
    );
    // Destructor
    ~Mesh();

private: 
    // Member variables for owning the data.
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures;

    // OpenGL objects
    VAO vao; 
    VBO vbo;
    EBO ebo;

    GLuint shaderID;
    int numDiffuse = 0;
    int numSpecular = 0;

};

#endif

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