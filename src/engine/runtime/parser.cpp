#include "parser.h"

#include "stb/stb_img.h"
#include <fastgltf/core.hpp>
#include <fastgltf/tools.hpp>      // accessor tools live here
#include <fastgltf/types.hpp>
#include <fastgltf/glm_element_traits.hpp>

unsigned int hash(const std::vector<unsigned char>& data) {
    unsigned int h = 5381;
    for (size_t i = 0; i < data.size(); ++i)
        h = h * 31 + data[i];
    return h;
}

unsigned char* stbiLoadEmbedded(unsigned char* data, int data_len, int* width, int* height) {
    int channelsRGBA = 4;
    unsigned char* pixels = stbi_load_from_memory(data, data_len, width, height, &channelsRGBA, 4);
    return pixels;
}

unsigned char* stbiLoadDir(std::string dir, int* width, int* height) {
    int channelsRGBA = 4;
    unsigned char* pixels = stbi_load(dir.c_str(), width, height, &channelsRGBA, 4);
    return pixels;
}

void Parser::loadShameCube() {
    vertices = errorVertices;
    indices = errorIndices;
    texHash.push_back(0);
}

Parser::Parser(std::string modelDir) {

    // Placeholder on file path fail
    std::filesystem::path path = modelDir;
    if (!std::filesystem::exists(path)) {
        std::cerr << "[ERROR][Parser] Invalid model path: " << modelDir << std::endl;
        loadShameCube();
        return;
    }

    // Placeholder if fastgltf error returns an error
    auto dataBuffer = fastgltf::GltfDataBuffer::FromPath(modelDir);
    if (dataBuffer.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Could not read file: " << modelDir << std::endl;
        loadShameCube();
        return;
    }

    // Actual parsing starts here.
    fastgltf::Parser parser;
    auto loadedAsset = parser.loadGltf(dataBuffer.get(), path.parent_path(), fastgltf::Options::LoadExternalBuffers);
    // Placeholder if parser returns error
    if (loadedAsset.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Failed to parse glTF: " << modelDir << " - " << fastgltf::getErrorMessage(loadedAsset.error()) << std::endl;
        loadShameCube();
        return;
    }

    fastgltf::Asset& asset = loadedAsset.get();

    for (size_t m = 0; m < asset.meshes.size(); ++m) {

        fastgltf::Mesh& mesh = asset.meshes[m];

        for (size_t p = 0; p < mesh.primitives.size(); ++p) {

            fastgltf::Primitive& prim = mesh.primitives[p];
            size_t baseVertex = vertices.size();

            fastgltf::Attribute* posAttr = prim.findAttribute("POSITION");
            fastgltf::Accessor& posAccessor = asset.accessors[posAttr->accessorIndex];
            
            vertices.resize(baseVertex + posAccessor.count);

            for (size_t v = 0; v < posAccessor.count; ++v) {
                auto pos = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, posAccessor, v);
                vertices[baseVertex + v].position = { pos.x(), pos.y(), pos.z() };
            }

            if (prim.indicesAccessor.has_value()) {
                fastgltf::Accessor& idxAccessor = asset.accessors[prim.indicesAccessor.value()];
                indices.reserve(indices.size() + idxAccessor.count);

                for (size_t i = 0; i < idxAccessor.count; ++i) {
                    auto index = fastgltf::getAccessorElement<unsigned int>(asset, idxAccessor, i);
                    indices.push_back(baseVertex + index);
                }
            }

        }
    }
    texHash.push_back(0);
}