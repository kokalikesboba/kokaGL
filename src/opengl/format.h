#ifndef FORMAT_H
#define FORMAT_H

#include "glm/glm.hpp"

#include <vector>

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

enum class TextureType {
	// PBR Only
    BaseColor,
	// PBR Only
	RoughnessMetallic,
	// PBR Only
	Occlusion,
	// PBR Only
	Normal,
	// PBR Only
	Emissive,
};

#endif