#ifndef PARSER_H
#define PARSER_H

#include "opengl/format.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <iostream>
#include <filesystem>
#include <memory>
#include <vector>

inline const std::vector<PNCUVertex> errorVertices = {
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

inline const std::vector<unsigned int> errorIndices = {
    0,  1,  2,   0,  2,  3,  // front
    4,  6,  5,   4,  7,  6,  // back
    8,  9,  10,  8,  10, 11, // left
    12, 14, 13,  12, 15, 14, // right
    16, 17, 18,  16, 18, 19, // top
    20, 22, 21,  20, 23, 22, // bottom
};

class Parser {
public: 
    Parser(std::string modelDir);
    
    std::vector<PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> texHash;
    std::vector<PBRTexType> texType;
    std::vector<std::vector<unsigned char>> texData;
    std::vector<int> texWidth;
    std::vector<int> texHeight;
private:
    void LoadShameMesh();
    void LoadShameTexture(PBRTexType errorType);
};

#endif