#ifndef FORMAT_H
#define FORMAT_H

#include <glm/glm.hpp>

#include <string>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

enum class textureType {
    Diffuse,
    Specular,
};

#endif