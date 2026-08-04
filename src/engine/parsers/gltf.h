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
#include <variant>

struct MeshRenderData {
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
    std::vector<MeshRenderData> data;
protected:
    RenderFormat::TextureData GetShameTexture(RenderFormat::TexType texType);
    void LoadShameModel();

    bool FilePathCheck();
    bool DataBufferCheck(const fastgltf::Expected<fastgltf::GltfDataBuffer>& databuffer);
    bool AssetCheck(const fastgltf::Expected<fastgltf::Asset>& loadedAsset);
    
    std::vector<RenderFormat::PNCUVertex> ParseVertices(const fastgltf::Primitive& primitive);
    std::vector<unsigned int> ParseIndices(const fastgltf::Primitive& primitive);
    std::vector<RenderFormat::TextureData> ParseTextureList(const fastgltf::Primitive& primitive);
    const glm::vec3 ParsePosition(const fastgltf::Node &node);
    const glm::quat ParseOrientation(const fastgltf::Node &node);
    const glm::vec3 ParseScale(const fastgltf::Node &node);

    void LoadTextureFromEmbedded(const std::size_t materialIndex, RenderFormat::TexType type, std::vector<RenderFormat::TextureData>& textures);
private:
    std::string modelDir;
    std::filesystem::path path;
    fastgltf::Parser parser;
    fastgltf::Asset asset;
};  

#endif