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
    partCount = asset.meshes.size();

    ModelRenderData entry{};
    for (auto& mesh : asset.meshes) {
        for (auto& buffer : mesh.primitives) {
            entry.vertices.emplace_back(std::move(ParseVertices(buffer)));
            entry.indices.emplace_back(std::move(ParseIndices(buffer)));

        }
    }

    RenderFormat::TextureData TextureData;
    for (auto& materials : asset.materials) {
        if (materials.pbrData.baseColorTexture.has_value()) {
            
        }
    }
}

void ParseGLTF::LoadShameModel()
{
    vertices.resize(1);
    indices.resize(1);
    texData.resize(1);

    vertices[0] = RenderFormat::errorVertices;
    indices[0] = RenderFormat::errorIndices;
    auto errorTex = RenderFormat::TextureData{
        2,
        2,
        0,
        RenderFormat::TexType::BaseColor,
        std::vector<unsigned char>{}
    };
    texData[0].push_back(errorTex); 
}

void ParseGLTF::LoadShameTexture(int meshIndex, int texIndex)
{
    texData[meshIndex][texIndex] = RenderFormat::TextureData
    {
        2,
        2,
        0,
        TexType::BaseColor,
        std::vector<unsigned char>{}
    };
}

bool ParseGLTF::FilePathCheck()
{
    if (!std::filesystem::exists(path)) {
        std::cerr << "[ERROR][Parser] Invalid model path: " << modelDir << std::endl;
        LoadShameModel();
        return false;
    }
    return true;
}

bool ParseGLTF::DataBufferCheck(const fastgltf::Expected<fastgltf::GltfDataBuffer>& databuffer)
{
    if (databuffer.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Could not read file: " << modelDir << std::endl;
        LoadShameModel();
        return false;
    }
    return true;
}

bool ParseGLTF::AssetCheck(const fastgltf::Expected<fastgltf::Asset>& loadedAsset)
{
    if (loadedAsset.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Failed to parse glTF: " << modelDir << " - " << fastgltf::getErrorMessage(loadedAsset.error()) << std::endl;
        LoadShameModel();
        return false;
    }
    return true;
}

std::vector<RenderFormat::PNCUVertex> ParseGLTF::ParseVertices(fastgltf::Primitive &buffer)
{
    fastgltf::Attribute* posAttr = buffer.findAttribute("POSITION");
    fastgltf::Accessor& posAccessor = asset.accessors[posAttr->accessorIndex];

    std::vector<RenderFormat::PNCUVertex> vertexEntry;
    vertexEntry.resize(posAccessor.count);

    for (size_t i = 0; i < posAccessor.count; ++i) {
        auto pos = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, posAccessor, i);
        vertexEntry[i].position = {pos.x(), pos.y(), pos.z()};
    }

    fastgltf::Attribute* normalAttribute = buffer.findAttribute("NORMAL");
    fastgltf::Accessor& normalAccessor = asset.accessors[normalAttribute->accessorIndex];
    for (size_t i = 0; i < normalAccessor.count; ++i) {
        auto normal = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, normalAccessor, i);
        vertexEntry[i].normal = {normal.x(), normal.y(), normal.z()};
    } 

    fastgltf::Attribute* uvAttribute = buffer.findAttribute("TEXCOORD_0");
    fastgltf::Accessor& uvAccessor = asset.accessors[uvAttribute->accessorIndex];
    for (size_t i = 0; i < posAccessor.count; ++i) {
        auto uv = fastgltf::getAccessorElement<fastgltf::math::fvec2>(asset, uvAccessor, i);
        vertexEntry[i].uv = {uv.x(), uv.y()};    
    }
    return vertexEntry;
}

std::vector<unsigned int> ParseGLTF::ParseIndices(fastgltf::Primitive &buffer)
{
    std::vector<unsigned int> indexEntry;
    if (buffer.indicesAccessor.has_value()) {
        fastgltf::Accessor& idxAccessor = asset.accessors[buffer.indicesAccessor.value()];

        for (size_t i = 0; i < idxAccessor.count; ++i) {
            auto index = fastgltf::getAccessorElement<unsigned int>(asset, idxAccessor, i);
            indexEntry.push_back(index);
        }
    }
}

RenderFormat::TextureData ParseGLTF::ParseTexture(fastgltf::Material &material)
{
    auto& texture = asset.textures[material.pbrData.baseColorTexture->textureIndex];
        auto& image = asset.images[texture.imageIndex.value()];

        auto* bufferViewSource = std::get_if<fastgltf::sources::BufferView>(&image.data);
        if (!bufferViewSource) {
            LoadShameTexture(0,0);
            continue;
        }

        auto& bufferView = asset.bufferViews[bufferViewSource->bufferViewIndex];
        auto& buffer     = asset.buffers[bufferView.bufferIndex];

        auto* bufferArray = std::get_if<fastgltf::sources::Array>(&buffer.data);
        if (!bufferArray) {
            LoadShameTexture(0,0);
            continue;
        }

        const unsigned char* base = reinterpret_cast<const unsigned char*>(bufferArray->bytes.data());
        const unsigned char* pngData = base + bufferView.byteOffset;
        size_t pngLength = bufferView.byteLength;

        ParsePNG png(pngData, pngLength);
        if (png.data == nullptr) {
            LoadShameTexture(0,0);
            continue;
        }
        std::vector<unsigned char> bytes(png.data, png.data + png.width * png.height * 4);

        std::vector<RenderFormat::TextureData> texEntry;
        
        texEntry.push_back(
            {
                png.width,
                png.height,
                png.hash,
                TexType::BaseColor,
                bytes
            }
        );
        
        texData.emplace_back(std::move(texEntry));
    } else {
    LoadShameTexture(0,0);
}
