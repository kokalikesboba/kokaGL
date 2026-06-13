#ifndef MODEL_H
#define MODEL_H

#include "opengl/drawable/mesh.h"
#include "opengl/format.h"
#include "glad/glad.h"

#include "engine/runtime/texturepool.h"
#include "engine/runtime/parser.h"

#include <iostream>
#include <memory>

static const std::vector<Vertex> kErrorVertices = {
    // position              // normal           // color (magenta)    // uv
    // Front
    {{ 0.5f,  0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f,  0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f, -0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{ 0.5f, -0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    // Back
    {{ 0.5f,  0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f,  0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f, -0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    {{ 0.5f, -0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    // Left
    {{-0.5f,  0.5f,  0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f,  0.5f, -0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f, -0.5f, -0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{-0.5f, -0.5f,  0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    // Right
    {{ 0.5f,  0.5f,  0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{ 0.5f,  0.5f, -0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{ 0.5f, -0.5f, -0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    {{ 0.5f, -0.5f,  0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    // Top
    {{ 0.5f,  0.5f, -0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    {{-0.5f,  0.5f, -0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{-0.5f,  0.5f,  0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{ 0.5f,  0.5f,  0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    // Bottom
    {{ 0.5f, -0.5f, -0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
    {{-0.5f, -0.5f, -0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
    {{-0.5f, -0.5f,  0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
    {{ 0.5f, -0.5f,  0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
};

static const std::vector<GLuint> kErrorIndices = {
    0,  1,  2,   0,  2,  3,  // front
    4,  6,  5,   4,  7,  6,  // back
    8,  9,  10,  8,  10, 11, // left
    12, 14, 13,  12, 15, 14, // right
    16, 17, 18,  16, 18, 19, // top
    20, 22, 21,  20, 23, 22, // bottom
};

static  unsigned char fallbackPixels[] = {
    255, 0, 255, 255,  0, 0, 0, 255,    // Row 1: Pink, Black
    0, 0, 0, 255,     255, 0, 255,255     // Row 2: Black, Pink
};


class Model
{
public:
    Model(const std::string& modelDir, TexturePool& texturepool);
    void Draw(const Shader& shader) const;

    void SetPosition(glm::vec3 position);
    void AddPosition(glm::vec3 position);
    glm::vec3 GetPosition() const;

    void SetEulerRotation(glm::vec3 rotation);
    void AddEulerRotation(glm::vec3 rotation);
    void SetOrientation(glm::quat orientation);
    glm::quat GetOrientation() const;

private:
    std::unique_ptr<Mesh> mesh;

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::quat orientation = {1.f, 0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f, 1.f, 1.f};
};
 
#endif