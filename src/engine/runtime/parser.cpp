#include "parser.h"

unsigned int hash(const std::vector<unsigned char>& data) {
    unsigned int h = 5381;
    for (size_t i = 0; i < data.size(); ++i)
        h = h * 31 + data[i];
    return h;
}

Parser::Parser(std::string modelDir)
{
    std::filesystem::path path = modelDir;
    if (!std::filesystem::exists(path)) {
        std::cerr << "[ERROR][Parser] Invalid model path: " << modelDir << std::endl;
        vertices = errorVertices;
        indices = errorIndices;
        texHash.push_back(0);
        return;
    }

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        modelDir,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType
    );

    for (int i = 0; i < scene->mNumMeshes; ++i) {
        
    }
}