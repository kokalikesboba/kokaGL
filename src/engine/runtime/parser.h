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

class Parser {
public: 
    Parser(std::string modelDir);
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned char&> textureData;
    std::vector<std::string> textureHash;
private:
    
};

#endif