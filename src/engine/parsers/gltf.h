#ifndef GLTF_H
#define GLTF_H

#include "formats/rendererformat.hpp"
#include "engine/parsers/png.h"

#include "fastgltf/core.hpp"
#include "fastgltf/tools.hpp"
#include "fastgltf/types.hpp"
#include "fastgltf/glm_element_traits.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <memory>


    struct PNCUVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 uv;
    };
    
struct ModelRenderData {
    std::vector<RenderFormat::PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<RenderFormat::TextureData> texData;
    glm::vec3 position;
    glm::quat orientation;
    glm::vec3 scale;
};

class ParseGLTF {
public:
    ParseGLTF(const std::string& modelDir);
    std::vector<ModelRenderData> data;
    int partCount;
protected:
    void LoadShameModel();
    void LoadShameTexture(int meshIndex, int texIndex);

    bool FilePathCheck();
    bool DataBufferCheck(const fastgltf::Expected<fastgltf::GltfDataBuffer>& databuffer);
    bool AssetCheck(const fastgltf::Expected<fastgltf::Asset>& loadedAsset);

    std::vector<RenderFormat::PNCUVertex> ParseVertices(fastgltf::Primitive &buffer);
    std::vector<unsigned int> ParseIndices(fastgltf::Primitive &buffer);
    
    RenderFormat::TextureData ParseTexture(fastgltf::Material &material);
private:
    std::string modelDir;
    std::filesystem::path path;
    fastgltf::Parser parser;
    fastgltf::Asset asset;
};  

#endif