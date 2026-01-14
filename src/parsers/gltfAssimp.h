#ifndef MODEL_ASSIMP_H
#define MODEL_ASSIMP_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "opengl/format.h" 

// Use a struct to return both at once
struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

inline MeshData loadModelData(const char* path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, 
        aiProcess_Triangulate | 
        aiProcess_JoinIdenticalVertices |
        aiProcess_FlipUVs
    );

    if (!scene) {
        // Print to standard error before throwing
        std::cerr << "CRITICAL: Assimp could not read file at: " << path << std::endl;
        std::cerr << "Reason: " << importer.GetErrorString() << std::endl;
        throw std::runtime_error(importer.GetErrorString());
    }

    MeshData data;
    unsigned int vertexOffset = 0;

    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[m];

        // 1. Extract UNIQUE vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

            Vertex v{};
            v.position = { 
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
            };
            if (mesh->HasNormals()) {
                v.normal = { 
                    mesh->mNormals[i].x,
                    mesh->mNormals[i].y,
                    mesh->mNormals[i].z
                };
            }
            if (mesh->mTextureCoords[0]) {
                v.texUV = {
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y
                };
            }
            
            data.vertices.push_back(v);
        }

        // 2. Extract Indices and offset them based on previous meshes
        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace face = mesh->mFaces[f];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                data.indices.push_back(face.mIndices[j] + vertexOffset);
            }
        }

        vertexOffset += mesh->mNumVertices;
    }
    
    return data;
}

#endif