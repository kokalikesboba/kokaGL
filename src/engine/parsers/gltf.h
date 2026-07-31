#ifndef GLTF_H
#define GLTF_H

#include "formats/rendererformat.hpp"
#include "engine/parsers/png.h"

#include "fastgltf/core.hpp"
#include "fastgltf/tools.hpp"
#include "fastgltf/types.hpp"
#include "fastgltf/glm_element_traits.hpp"

// TODO: Temporary?
#include "glm/gtx/quaternion.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <memory>
#include <utility>

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
protected:
    RenderFormat::TextureData GetShameTexture(RenderFormat::TexType texType);
    void LoadShameModel();

    bool FilePathCheck();
    bool DataBufferCheck(const fastgltf::Expected<fastgltf::GltfDataBuffer>& databuffer);
    bool AssetCheck(const fastgltf::Expected<fastgltf::Asset>& loadedAsset);
    
    std::vector<RenderFormat::PNCUVertex> ParseVertices(int meshIndex);
    std::vector<unsigned int> ParseIndices(int meshIndex);
    std::vector<RenderFormat::TextureData> ParseTextureList(int meshIndex);
private:
    std::string modelDir;
    std::filesystem::path path;
    fastgltf::Parser parser;
    fastgltf::Asset asset;
};  

#endif