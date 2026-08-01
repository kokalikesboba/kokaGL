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

    for (int i = 0; i < asset.meshes.size(); ++i) {
        data.emplace_back(ModelRenderData{
            std::move(ParseVertices(i)),
            std::move(ParseIndices(i)),
            std::move(ParseTextureList(i)),
            {0.f, 0.f, 0.f},
            {1.f, 0.f, 0.f, 0.f},
            {1.f, 1.f, 1.f}
        });
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
        ModelRenderData{
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
        std::cerr << "[ERROR][Parser] Invalid model path: " << modelDir << "\n";
        LoadShameModel();
        return false;
    }
    return true;
}

bool ParseGLTF::DataBufferCheck(const fastgltf::Expected<fastgltf::GltfDataBuffer>& databuffer)
{
    if (databuffer.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Could not read file: " << modelDir << "\n";
        LoadShameModel();
        return false;
    }
    return true;
}

bool ParseGLTF::AssetCheck(const fastgltf::Expected<fastgltf::Asset>& loadedAsset)
{
    if (loadedAsset.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Failed to parse glTF: " << modelDir << " - " << fastgltf::getErrorMessage(loadedAsset.error()) << "\n";
        LoadShameModel();
        return false;
    }

    // Complain if more than one scene exists.
    if (asset.scenes.size() > 1) {
        std::cerr << "[WARN][Parser] More than one scene found in: " << "\n";
    };
    // Complain if camera found
    if (!asset.cameras.empty()) {
        std::cerr << "[WARN][Parser] Camera found in: " << modelDir << "\n";
    }
    // Complain if light found
    if (!asset.lights.empty()) {
        std::cerr << "[WARN][Parser] Light found in: " << modelDir << "\n";
    }
    return true;
}

std::vector<RenderFormat::PNCUVertex> ParseGLTF::ParseVertices(int meshIndex)
{

    std::vector<RenderFormat::PNCUVertex> vertices;

    auto& primitive = asset.meshes[meshIndex].primitives[0];

    fastgltf::Attribute* posAttr = primitive.findAttribute("POSITION");
    fastgltf::Accessor& posAccessor = asset.accessors[posAttr->accessorIndex];

    vertices.resize(posAccessor.count);

    for (size_t i = 0; i < posAccessor.count; ++i) {
        auto pos = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, posAccessor, i);
        vertices[i].position = {pos.x(), pos.y(), pos.z()};
    }

    fastgltf::Attribute* normalAttribute = primitive.findAttribute("NORMAL");
    fastgltf::Accessor& normalAccessor = asset.accessors[normalAttribute->accessorIndex];
    for (size_t i = 0; i < normalAccessor.count; ++i) {
        auto normal = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, normalAccessor, i);
        vertices[i].normal = {normal.x(), normal.y(), normal.z()};
    } 

    fastgltf::Attribute* uvAttribute = primitive.findAttribute("TEXCOORD_0");
    fastgltf::Accessor& uvAccessor = asset.accessors[uvAttribute->accessorIndex];
    for (size_t i = 0; i < posAccessor.count; ++i) {
        auto uv = fastgltf::getAccessorElement<fastgltf::math::fvec2>(asset, uvAccessor, i);
        vertices[i].uv = {uv.x(), uv.y()};    
    }
    return vertices;
}

std::vector<unsigned int> ParseGLTF::ParseIndices(int meshIndex)
{
    std::vector<unsigned int> indices;

    auto& primitive = asset.meshes[meshIndex].primitives[0];

    // TODO: theres probably a better way to do this.
    if (!primitive.indicesAccessor.has_value()) throw std::runtime_error("No indices found- aborting.");
    
    fastgltf::Accessor& idxAccessor = asset.accessors[primitive.indicesAccessor.value()];

    for (size_t i = 0; i < idxAccessor.count; ++i) {
        auto index = fastgltf::getAccessorElement<unsigned int>(asset, idxAccessor, i);
        indices.push_back(index);
    }
    
    return indices;
}

std::vector<RenderFormat::TextureData> ParseGLTF::ParseTextureList(int meshIndex)
{
    std::vector<RenderFormat::TextureData> textures;

    // TODO: unused as of now
    float metallicFactor;
    float roughnessFactor;
    
    // If material doesn't exist, create a list of the default textures
    if(!asset.meshes[meshIndex].primitives[0].materialIndex.has_value()) {
        std::cerr << "[WARN][Parser] Model has no material: " << modelDir << "\n";
        textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::BaseColor)));
        textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::ORM)));
        textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::Normal)));
        return textures;
    }

    const auto& materialIndex = asset.meshes[meshIndex].primitives[0].materialIndex.value();
 
    roughnessFactor = asset.materials[materialIndex].pbrData.roughnessFactor;
    metallicFactor = asset.materials[materialIndex].pbrData.metallicFactor;

    const auto& textureIndex = asset.materials[materialIndex].pbrData.baseColorTexture.value().textureIndex;

    const auto& imageIndex = asset.textures[textureIndex].imageIndex.value();
    const auto& imageData = asset.images[imageIndex].data;
    
    auto* bufferView = std::get_if<fastgltf::sources::BufferView>(&imageData);
    if (!bufferView) throw std::runtime_error("Texture is not embedded in glb");
    const auto& view = asset.bufferViews[bufferView->bufferViewIndex];
    const auto& buffer = asset.buffers[view.bufferIndex];
    auto* arr = std::get_if<fastgltf::sources::Array>(&buffer.data);
    if (!arr) throw std::runtime_error("[Parser] buffer not loaded");
    const std::byte* start = arr->bytes.data() + view.byteOffset;
    std::size_t size = view.byteLength;
    
    ParsePNG parsed(reinterpret_cast<const unsigned char*>(start), size);
    RenderFormat::TextureData baseColor;

    textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::ORM)));
    textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::ORM)));
    textures.emplace_back(std::move(GetShameTexture(RenderFormat::TexType::Normal)));

    return textures;
}