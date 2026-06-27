#ifndef FORMAT_H
#define FORMAT_H

#include "glm/glm.hpp"

#include <vector>

struct BillboardVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 uv;
};

enum class TextureType {
    BaseColor,
	RoughnessMetallic,
	Occlusion,
	Normal,
	Emissive,
	Billboard,
};

#endif