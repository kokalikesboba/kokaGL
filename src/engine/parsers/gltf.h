#ifndef GLTF_H
#define GLTF_H

#include "engine/formats/rendererformat.hpp"
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
    std::vector<RenderFormat::PNCUVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<RenderFormat::TextureInfo> texInfo;
    std::vector<std::vector<unsigned char>> texData;
private:
    void LoadShameMesh();
    void LoadShameTexture();
};

#endif