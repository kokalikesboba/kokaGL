#ifndef GLTF_H
#define GLTF_H

#include "formats/renderformat.hpp"
#include "engine/parsers/png.h"

#include "fastgltf/core.hpp"
#include "fastgltf/tools.hpp"
#include "fastgltf/types.hpp"
#include "fastgltf/glm_element_traits.hpp"

#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <memory>
#include <utility>
#include <variant>

struct PrimitiveRenderData {
    std::vector<RenderFormat::PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<RenderFormat::TextureData> texData;
    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::quat orientation = {1.f, 0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f, 1.f, 1.f};
    // float pbrRoughness;
    // float pbrMetallic;
};

class ParseGLTF {
public:
    ParseGLTF(const std::string& modelDir);
    std::vector<PrimitiveRenderData> data;
protected:
    RenderFormat::TextureData GetShameTexture(RenderFormat::TexType texType);
    void LoadShameModel();

    bool FilePathCheck();
    bool DataBufferCheck(const fastgltf::Expected<fastgltf::GltfDataBuffer>& databuffer);
    bool AssetCheck(const fastgltf::Expected<fastgltf::Asset>& loadedAsset);
    
    const std::vector<RenderFormat::PNCUVertex> ParseVertices(const fastgltf::Primitive& primitive);
    const std::vector<unsigned int> ParseIndices(const fastgltf::Primitive& primitive);
    const std::vector<RenderFormat::TextureData> ParseTextureList(const fastgltf::Primitive& primitive);

    const glm::vec3 ParsePosition(const fastgltf::Node &node) const;
    const glm::quat ParseOrientation(const fastgltf::Node &node) const;
    const glm::vec3 ParseScale(const fastgltf::Node &node) const;

    void LoadTextureFromEmbedded(const std::size_t materialIndex, RenderFormat::TexType type, std::vector<RenderFormat::TextureData>& textures);
private:
    std::string modelDir;
    std::filesystem::path path;
    fastgltf::Parser parser;
    fastgltf::Asset asset;
};  

#endif