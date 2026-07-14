#include "gizmo.h"

Gizmo::Gizmo(const std::string imgDir)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* texData = stbi_load(imgDir.c_str(), &this->width, &this->height, nullptr, 4);
    this->texture = std::make_unique<Texture>(PBRTexType::BaseColor);
    this->texture->genRGBATexture(texData, this->width , this->height);
    stbi_image_free(texData);
    
    billboard = std::make_unique<Billboard>(this->texture.get());
    stbi_set_flip_vertically_on_load(false);
}

void Gizmo::Draw(Shader& shader)
{
    billboard->Draw(shader, position, scale);
}