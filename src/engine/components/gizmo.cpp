#include "gizmo.h"

#include "stb/stb_img.h"

Gizmo::Gizmo(const std::string imgDir)
:
gizmoShader("shaders/billboard.vert", "shaders/billboard.frag")
{
    unsigned char* texData = stbi_load(imgDir.c_str(), &this->width, &this->height, nullptr, 4);
    this->texture = std::make_unique<Texture>(PBRTexType::BaseColor);
    this->texture->genRGBATexture(texData, this->width , this->height);
    stbi_image_free(texData);
    
    billboard = std::make_unique<Billboard>(this->texture.get());
}

void Gizmo::Draw()
{
    billboard->Draw(gizmoShader);
}