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
        std::filesystem::path path = modelDir;
        if (!std::filesystem::exists(path)) {
            std::cerr << "[ERROR][Parser] Invalid model path: " << modelDir << std::endl;
            loadShameCube();
            return;
        }

        auto buffExp = fastgltf::GltfDataBuffer::FromPath(modelDir);
        if (buffExp.error() != fastgltf::Error::None) {
            std::cerr << "[ERROR][Parser] Error while parsing." << std::endl;
            loadShameCube();
            return;
        } else {
            std::cerr << "stub!" << std::endl;
            loadShameCube();
            return;
        }
    }
