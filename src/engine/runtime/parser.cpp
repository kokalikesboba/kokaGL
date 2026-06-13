#include "parser.h"

unsigned int hash(std::vector<unsigned char>& data) {
    unsigned int hash = 5831;
    for (int i = 0; i < data.size(); ++i) {
        hash = hash * 31 + data[i];
    }
    return hash;
}

Parser::Parser(std::string modelDir)
{
    std::filesystem::path path = modelDir;
    if (std::filesystem::exists(path)) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(
            modelDir,
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType 
        );
    } else {
        std::cout << "Invalid path" << std::endl;
    }
}