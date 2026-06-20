#include "texturepool.h"

TexturePool::TexturePool()
{
	// Initializes the black and magenta fallback texture.
    errorTex = std::make_shared<Texture>(textureType::BaseColor);
	errorTex->genRGBATexture(fallbackPixels.data(), 2, 2);
	cache.insert({0, errorTex});
}

// Adds a texture to be observed by the pool while also buffering it to the GPU. Callers are responsible for keeping the returned pointer alive.
std::shared_ptr<Texture> TexturePool::Add(unsigned int texHash, textureType textype, std::vector<unsigned char>& bytes, int width, int height)
{
	if (cache.find(texHash) == cache.end()) {
		std::shared_ptr<Texture> buffer = std::make_shared<Texture>(textype);
		buffer->genRGBATexture(bytes.data(), width, height);
		cache.insert({texHash, buffer});
		std::cout << "[Success][Texturepool] Inserted a texture into cache with hash of: " << texHash << std::endl;
		return buffer;
	} else {
		std::cerr << "[ERROR][TexturePool] Attempted to add a texture whose texHash already exists: " << texHash << std::endl;
		++errorTexInstances;
		return errorTex;
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

// Gets a live Texture for the hash, or the fallback if missing/expired.
std::shared_ptr<Texture> TexturePool::Get(unsigned int texHash)
{
	if (!texHash) std::cerr << "[WARN][TexturePool] A model requested a hash of 0, this is likely from a failed parse." << std::endl; 

    auto it = cache.find(texHash);
    if (it != cache.end()) {
        std::shared_ptr<Texture> tex = it->second.lock();
        if (tex)
            return tex;          // present and alive
    }
    std::cerr << "[ERROR][TexturePool] Tried to get a Texture with an invalid hash: " << texHash << std::endl;
    ++errorTexInstances;
    return errorTex;
}
