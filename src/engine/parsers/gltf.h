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

class ParseGLTF {
public:
    ParseGLTF(const std::string& modelDir);
    std::vector<std::vector<RenderFormat::PNCUVertex>> vertices;
    std::vector<std::vector<unsigned int>> indices;
    std::vector<std::vector<RenderFormat::TextureData>> texData;
    int meshCount;
private:
    void LoadShameModel();
    void LoadShameTexture(int meshIndex, int texIndex);
};  

#endif