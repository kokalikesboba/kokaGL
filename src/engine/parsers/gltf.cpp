#include "gltf.h"

using namespace RenderFormat;

// I'm struggling to read the syntax a little bit, so member variables using this-> is intentional
ParseGLTF::ParseGLTF(const std::string& modelDir) :
    modelDir(modelDir)
{
    this->path = std::filesystem::path(modelDir);
    if (!FilePathCheck()) return;

    auto databuffer = fastgltf::GltfDataBuffer::FromPath(path);
    if (!DataBufferCheck(databuffer)) return;

    auto loadedAsset = this->parser.loadGltf(databuffer.get(), path.parent_path(), fastgltf::Options::LoadExternalBuffers);
    if (!AssetCheck(loadedAsset)) return;
    asset = std::move(loadedAsset.get());

    // loop through the span of nodes
    for (const auto& node : asset.nodes) {

        if (!node.meshIndex.has_value()) throw std::runtime_error("[ERROR][ParseGLTF] Nodes have no meshes");
        // at that node, get the mesh we want to modify.
        auto meshIndex = node.meshIndex.value();
        // at this mesh, loop through the span of it's primitives
        for (const auto& primitive : asset.meshes[meshIndex].primitives) {
            MeshRenderData part;

            // at this primitive, get the relevant vertices
            part.vertices = std::move(ParseVertices(primitive));
            part.indices = std::move(ParseIndices(primitive));
            part.texData = std::move(ParseTextureList(primitive));
            // because primitives don't have their own transform, get the transform at the currently vi sited node.
            part.position = ParsePosition(node);
            part.orientation = ParseOrientation(node);
            part.scale = ParseScale(node);

            data.emplace_back(std::move(part));
        }
    }
}

RenderFormat::TextureData ParseGLTF::GetShameTexture (RenderFormat::TexType texType)
{
    RenderFormat::TextureData defaultTexturelist;
    defaultTexturelist =
    {
        2,
        2,
        // TODO: Stupid fucking workaround.
        static_cast<unsigned int>(std::to_underlying<RenderFormat::TexType>(texType)),
        texType,
        RenderFormat::fallbackTexture
    };
    return defaultTexturelist;
}

void ParseGLTF::LoadShameModel()
{
    std::vector<RenderFormat::TextureData> textureList;
    textureList.emplace_back(GetShameTexture(RenderFormat::TexType::BaseColor));
    textureList.emplace_back(GetShameTexture(RenderFormat::TexType::ORM));
    textureList.emplace_back(GetShameTexture(RenderFormat::TexType::Normal));

    data.push_back(
        MeshRenderData{
            RenderFormat::errorVertices,
            RenderFormat::errorIndices,
            textureList,
            {0.f, 0.f, 0.f},
            {1.f, 0.f, 0.f, 0.f},
            {1.f, 1.f, 1.f}
        }
    );
}

bool ParseGLTF::FilePathCheck()
{
    if (!std::filesystem::exists(path)) {
        std::cerr << "[ERROR][ParseGLTF] Invalid model path: " << modelDir << "\n";
        LoadShameModel();
        return false;
    }
    return true;
}

bool ParseGLTF::DataBufferCheck(const fastgltf::Expected<fastgltf::GltfDataBuffer>& databuffer)
{
    if (databuffer.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][ParseGLTF] Could not read file: " << modelDir << "\n";
        LoadShameModel();
        return false;
    }
    return true;
}

bool ParseGLTF::AssetCheck(const fastgltf::Expected<fastgltf::Asset>& loadedAsset)
{
    if (loadedAsset.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][ParseGLTF] Failed to parse glTF: " << modelDir << " - " << fastgltf::getErrorMessage(loadedAsset.error()) << "\n";
        LoadShameModel();
        return false;
    }

    // Complain if more than one scene exists.
    if (asset.scenes.size() > 1) {
        std::cerr << "[WARN][ParseGLTF] More than one scene found in: " << "\n";
    };
    // Complain if camera found
    if (!asset.cameras.empty()) {
        std::cerr << "[WARN][ParseGLTF] Camera found in: " << modelDir << "\n";
    }
    // Complain if light found
    if (!asset.lights.empty()) {
        std::cerr << "[WARN][ParseGLTF] Light found in: " << modelDir << "\n";
    }
    return true;
}

std::vector<RenderFormat::PNCUVertex> ParseGLTF::ParseVertices(const fastgltf::Primitive& primitive)
{

    std::vector<RenderFormat::PNCUVertex> vertices;

    const fastgltf::Attribute* posAttr = primitive.findAttribute("POSITION");
    const fastgltf::Accessor& posAccessor = asset.accessors[posAttr->accessorIndex];

    vertices.resize(posAccessor.count);

    for (size_t i = 0; i < posAccessor.count; ++i) {
        auto pos = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, posAccessor, i);
        vertices[i].position = {pos.x(), pos.y(), pos.z()};
    }

    const fastgltf::Attribute* normalAttribute = primitive.findAttribute("NORMAL");
    const fastgltf::Accessor& normalAccessor = asset.accessors[normalAttribute->accessorIndex];
    for (size_t i = 0; i < normalAccessor.count; ++i) {
        auto normal = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, normalAccessor, i);
        vertices[i].normal = {normal.x(), normal.y(), normal.z()};
    } 

    const fastgltf::Attribute* uvAttribute = primitive.findAttribute("TEXCOORD_0");
    const fastgltf::Accessor& uvAccessor = asset.accessors[uvAttribute->accessorIndex];
    for (size_t i = 0; i < posAccessor.count; ++i) {
        auto uv = fastgltf::getAccessorElement<fastgltf::math::fvec2>(asset, uvAccessor, i);
        vertices[i].uv = {uv.x(), uv.y()};    
    }
    return vertices;
}

std::vector<unsigned int> ParseGLTF::ParseIndices(const fastgltf::Primitive &primitive)
{
    std::vector<unsigned int> indices;

    const fastgltf::Accessor& idxAccessor = asset.accessors[primitive.indicesAccessor.value()];

    for (size_t i = 0; i < idxAccessor.count; ++i) {
        auto index = fastgltf::getAccessorElement<unsigned int>(asset, idxAccessor, i);
        indices.push_back(index);
    }
    
    return indices;
}

std::vector<RenderFormat::TextureData> ParseGLTF::ParseTextureList(const fastgltf::Primitive& primitive)
{
    std::vector<RenderFormat::TextureData> textures;

    // TODO: unused as of now
    float metallicFactor = 0;
    float roughnessFactor = 0;
    
    // No material case
    if(!primitive.materialIndex.has_value()) {
        std::cerr << "[WARN][ParseGLTF] Model has no material: " << modelDir << "\n";
        textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::BaseColor)));
        textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::ORM)));
        textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::Normal)));
        return textures;
    }

    const auto& materialIndex = primitive.materialIndex.value();
 
    roughnessFactor = asset.materials[materialIndex].pbrData.roughnessFactor;
    metallicFactor = asset.materials[materialIndex].pbrData.metallicFactor;

    // No texture case (individual)
    if (asset.materials[materialIndex].pbrData.baseColorTexture.has_value()) {
        LoadTextureFromEmbedded(materialIndex, RenderFormat::TexType::BaseColor, textures);
    } else GetShameTexture(RenderFormat::TexType::BaseColor);

    if (asset.materials[materialIndex].pbrData.metallicRoughnessTexture.has_value()) {
        LoadTextureFromEmbedded(materialIndex, RenderFormat::TexType::ORM, textures);
    } else GetShameTexture(RenderFormat::TexType::ORM);

    if (asset.materials[materialIndex].normalTexture.has_value()) {
        LoadTextureFromEmbedded(materialIndex, RenderFormat::TexType::Normal, textures);
    } else GetShameTexture(RenderFormat::TexType::Normal);

    return textures;
}

const glm::vec3 ParseGLTF::ParsePosition(const fastgltf::Node &node)
{
    const auto trs = std::get_if<fastgltf::TRS>(&node.transform);
    glm::vec3 position = {trs->translation[0], trs->translation[1], trs->translation[2]};
    return position;
}

const glm::quat ParseGLTF::ParseOrientation(const fastgltf::Node &node)
{
    const auto trs = std::get_if<fastgltf::TRS>(&node.transform);
    glm::quat orientation = {trs->rotation[3], trs->rotation[1], trs->rotation[2], trs->rotation[0]};
    return orientation;
}

const glm::vec3 ParseGLTF::ParseScale(const fastgltf::Node &node)
{
    const auto trs = std::get_if<fastgltf::TRS>(&node.transform);
    glm::vec3 scale = {trs->scale[0], trs->scale[1], trs->scale[2]};
    return scale;
}

void ParseGLTF::LoadTextureFromEmbedded(const std::size_t materialIndex, RenderFormat::TexType type, std::vector<RenderFormat::TextureData> &textures)
{
    RenderFormat::TextureData texture;

    // Close enough man
    unsigned long int textureIndex;
    if (type == RenderFormat::TexType::BaseColor) {
        textureIndex = asset.materials[materialIndex].pbrData.baseColorTexture.value().textureIndex;
    } else if (type == RenderFormat::TexType::ORM) {
        textureIndex = asset.materials[materialIndex].pbrData.metallicRoughnessTexture.value().textureIndex;
    } else  if (type == RenderFormat::TexType::Normal) {
        textureIndex = asset.materials[materialIndex].normalTexture.value().textureIndex;
    }    
    const auto& imageIndex = asset.textures[textureIndex].imageIndex.value();
    const auto& imageData = asset.images[imageIndex].data;
    
    auto* bufferView = std::get_if<fastgltf::sources::BufferView>(&imageData);
    if (!bufferView) throw std::runtime_error("[ERROR][ParseGLTF]Texture is not embedded in glb");
    const auto& view = asset.bufferViews[bufferView->bufferViewIndex];
    const auto& buffer = asset.buffers[view.bufferIndex];
    auto* arr = std::get_if<fastgltf::sources::Array>(&buffer.data);
    if (!arr) throw std::runtime_error("[ERROR][ParseGLTF] buffer not loaded");
    const std::byte* start = arr->bytes.data() + view.byteOffset;
    std::size_t size = view.byteLength;
    
    ParsePNG loaded(reinterpret_cast<const unsigned char*>(start), size);

    texture.width = loaded.width;
    texture.height = loaded.height;
    texture.hash = loaded.hash;
    texture.type = type;
    texture.bytes = std::move(loaded.bytes);

    textures.emplace_back(std::move(texture));
}
