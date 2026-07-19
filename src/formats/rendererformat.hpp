#ifndef RENDERFORMAT_H
#define RENDERFORMAT_H

#include "glm/glm.hpp"

#include <vector>

namespace RenderFormat {
    // Vertex struct that contains Position, Normal, UV 
    struct PNUVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    // Vertex struct that contains Position, Normal, Color, UV 
    struct PNCUVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 uv;
    };

    enum class TexType {
        BaseColor,
        RoughnessMetallic,
        Occlusion,
        Normal
    };

    struct TextureData {
        int width;
        int height;
        unsigned int hash;
        TexType type;
        std::vector<unsigned char> bytes;
    };

    // Default missing texture.
    inline std::vector<unsigned char> fallbackBytes = {
        227, 66, 107, 255,  
        66, 94, 135, 255,
        66, 94, 135, 255,
        227, 66, 107, 255
    };

    // Default missing cube vertices
    inline const std::vector<PNCUVertex> errorVertices = {
        // position              // normal           // color (magenta)    // uv
        // Front
        {{ 0.5f,  0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
        {{-0.5f,  0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
        {{-0.5f, -0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
        {{ 0.5f, -0.5f,  0.5f}, { 0.f,  0.f,  1.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
        // Back
        {{ 0.5f,  0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
        {{-0.5f,  0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
        {{-0.5f, -0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
        {{ 0.5f, -0.5f, -0.5f}, { 0.f,  0.f, -1.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
        // Left
        {{-0.5f,  0.5f,  0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
        // Right
        {{ 0.5f,  0.5f,  0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
        {{ 0.5f,  0.5f, -0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
        {{ 0.5f, -0.5f, -0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
        {{ 0.5f, -0.5f,  0.5f}, { 1.f,  0.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
        // Top
        {{ 0.5f,  0.5f, -0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
        {{-0.5f,  0.5f, -0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
        {{-0.5f,  0.5f,  0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
        {{ 0.5f,  0.5f,  0.5f}, { 0.f,  1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
        // Bottom
        {{ 0.5f, -0.5f, -0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f}},
        {{-0.5f, -0.5f, -0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.5f, -0.5f,  0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f}},
        {{ 0.5f, -0.5f,  0.5f}, { 0.f, -1.f,  0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f}},
    };

    // Default missing cube indices
    inline const std::vector<unsigned int> errorIndices = {
        0,  1,  2,   0,  2,  3,  // front
        4,  6,  5,   4,  7,  6,  // back
        8,  9,  10,  8,  10, 11, // left
        12, 14, 13,  12, 15, 14, // right
        16, 17, 18,  16, 18, 19, // top
        20, 22, 21,  20, 23, 22, // bottom
    };
}

#endif