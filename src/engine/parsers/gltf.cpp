#include "gltf.h"

using namespace RenderFormat;

ParseGLTF::ParseGLTF(const std::string& modelDir) {

    // Placeholder on file path fail
    std::filesystem::path path = modelDir;
    if (!std::filesystem::exists(path)) {
        std::cerr << "[ERROR][Parser] Invalid model path: " << modelDir << std::endl;
        LoadShameModel();
        return;
    }

    // Placeholder if fastgltf error returns an error
    auto dataBuffer = fastgltf::GltfDataBuffer::FromPath(modelDir);
    if (dataBuffer.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Could not read file: " << modelDir << std::endl;
        LoadShameModel();
        return;
    }

    // Actual parsing starts here.
    fastgltf::Parser parser;
    auto loadedAsset = parser.loadGltf(dataBuffer.get(), path.parent_path(), fastgltf::Options::LoadExternalBuffers);
    // Placeholder if parser returns error
    if (loadedAsset.error() != fastgltf::Error::None) {
        std::cerr << "[ERROR][Parser] Failed to parse glTF: " << modelDir << " - " << fastgltf::getErrorMessage(loadedAsset.error()) << std::endl;
        LoadShameModel();
        return;
    }

    fastgltf::Asset& asset = loadedAsset.get();
    meshCount= asset.meshes.size();
    vertices.reserve(meshCount);
    indices.reserve(meshCount);
    texData.reserve(meshCount);

    for (auto& mesh : asset.meshes) {

        for (auto& prim : mesh.primitives) {

            size_t baseVertex = vertices.size();

            fastgltf::Attribute* posAttr = prim.findAttribute("POSITION");
            fastgltf::Accessor& posAccessor = asset.accessors[posAttr->accessorIndex];

            std::vector<RenderFormat::PNCUVertex> vertexEntry;
            vertexEntry.resize(baseVertex + posAccessor.count);

            for (size_t i = 0; i < posAccessor.count; ++i) {
                auto pos = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, posAccessor, i);
                vertexEntry[baseVertex + i].position = {pos.x(), pos.y(), pos.z()};
            }

            fastgltf::Attribute* normalAttribute = prim.findAttribute("NORMAL");
            fastgltf::Accessor& normalAccessor = asset.accessors[normalAttribute->accessorIndex];
            for (size_t i = 0; i < normalAccessor.count; ++i) {
                auto normal = fastgltf::getAccessorElement<fastgltf::math::fvec3>(asset, normalAccessor, i);
                vertexEntry[baseVertex + i].normal = {normal.x(), normal.y(), normal.z()};
            } 

            fastgltf::Attribute* uvAttribute = prim.findAttribute("TEXCOORD_0");
            fastgltf::Accessor& uvAccessor = asset.accessors[uvAttribute->accessorIndex];
            for (size_t i = 0; i < posAccessor.count; ++i) {
                auto uv = fastgltf::getAccessorElement<fastgltf::math::fvec2>(asset, uvAccessor, i);
                vertexEntry[baseVertex + i].uv = {uv.x(), uv.y()};    
            }

            vertices.emplace_back(std::move(vertexEntry));

            std::vector<unsigned int> indexEntry;
            if (prim.indicesAccessor.has_value()) {
                fastgltf::Accessor& idxAccessor = asset.accessors[prim.indicesAccessor.value()];
                indexEntry.reserve(indices.size() + idxAccessor.count);

                for (size_t i = 0; i < idxAccessor.count; ++i) {
                    auto index = fastgltf::getAccessorElement<unsigned int>(asset, idxAccessor, i);
                    indexEntry.push_back(baseVertex + index);
                }
            }

            indices.emplace_back(std::move(indexEntry));
        }
    }

    for (auto& materials : asset.materials) {

        if (materials.pbrData.baseColorTexture.has_value()) {
            auto& texture = asset.textures[materials.pbrData.baseColorTexture->textureIndex];
            auto& image = asset.images[texture.imageIndex.value()];

            // Absolute fucking magic to me
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
