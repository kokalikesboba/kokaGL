#include "texturepool.h"

TexturePool::TexturePool()
{
	// Initializes the black and magenta fallback texture.
    errorTex = std::make_shared<Texture>();
	errorTex->GenRGBATexture(RenderFormat::TexType::BaseColor, RenderFormat::fallbackBytes.data(), 2, 2);
	cache.insert({0, errorTex});
}

std::shared_ptr<Texture> TexturePool::GetOrAdd(const RenderFormat::TextureData &textureData)
{
    if (isCachedAndAlive(textureData.hash)) {
        return Get(textureData.hash);
    } else {
        return Add(textureData);
    }
}

// Checks if the hash exists in the map, also checks if the stored pointer has expired and deletes it. 
bool TexturePool::isCachedAndAlive(unsigned int texHash)
{
	auto it = cache.find(texHash);
	if (it == cache.end()) {
		return false;
	}
	if (it->second.expired()) {
		cache.erase(it);
		return false;
	}
	return true;
}

// Adds a texture to be observed by the pool while buffering it to the GPU
std::shared_ptr<Texture> TexturePool::Add(const RenderFormat::TextureData& textureData)
{
	if (cache.find(textureData.hash) == cache.end()) {
		std::shared_ptr<Texture> buffer = std::make_shared<Texture>();
		buffer->GenRGBATexture(textureData.type, textureData.bytes.data(), textureData.width, textureData.height);
		cache.insert({textureData.hash, buffer});
		std::cout << "[VERBOSE][Texturepool] Inserted a texture into cache with hash of: " << textureData.hash << std::endl;
		return buffer;
	} else {
		std::cerr << "[ERROR][TexturePool] Attempted to add a texture whose texHash already exists: " << textureData.hash << std::endl;
		++errorTexInstances;
		return errorTex;
	}
}

// Gets a live Texture for the hash, or the fallback if missing/expired.
std::shared_ptr<Texture> TexturePool::Get(unsigned int texHash)
{
	if (!texHash) std::cerr << "[WARN][TexturePool] A model requested a hash of 0, this is likely from a failed parse." << std::endl; 

    auto it = cache.find(texHash);
    if (it != cache.end()) {
        std::shared_ptr<Texture> tex = it->second.lock();
		std::cout << "[VERBOSE][TexturePool] Hit cache: " << texHash << std::endl;
        if (tex) return tex; // present and alive
    }
    std::cerr << "[ERROR][TexturePool] Tried to get a Texture with an invalid hash: " << texHash << std::endl;
    ++errorTexInstances;
    return errorTex;
}
