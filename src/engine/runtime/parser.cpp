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

    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
    std::cerr << "[ERROR][Parser] Assimp failed to load '" << modelDir
              << "': " << importer.GetErrorString() << "\n";
        vertices = errorVertices;
        indices = errorIndices;
        texHash.push_back(0);
        return;
    }

    // if (scene->mNumTextures == 0) {
    //    std::cerr << "[ERROR][Parser] No embedded texture found in: " << modelDir << std::endl;
    //}
    texHash.push_back(0);

    for (int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[i];

        for (int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];

            for (int k = 0; k < face.mNumIndices; ++k)
                indices.push_back(face.mIndices[k]);
        }
    }

    const aiMesh* mesh = scene->mMeshes[0];   // single-mesh for now

// Vertices: one Vertex per mNumVertices, pulled from parallel attribute arrays.
    for (unsigned int v = 0; v < mesh->mNumVertices; ++v) {
        Vertex vert;

        vert.position = { mesh->mVertices[v].x,
                        mesh->mVertices[v].y,
                        mesh->mVertices[v].z };

        if (mesh->HasNormals())
            vert.normal = { mesh->mNormals[v].x,
                            mesh->mNormals[v].y,
                            mesh->mNormals[v].z };

        if (mesh->mTextureCoords[0])   // UV channel 0 may be absent
            vert.texUV = { mesh->mTextureCoords[0][v].x,
                        mesh->mTextureCoords[0][v].y };
        else
            vert.texUV = { 0.0f, 0.0f };

        vertices.push_back(vert);
    }
}