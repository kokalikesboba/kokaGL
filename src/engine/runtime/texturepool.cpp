#include "texturepool.h"

TexturePool::TexturePool()
{
	// Initializes the black and magenta fallback texture.
    errorTex = std::make_shared<Texture>(textureType::BaseColor);
	errorTex->genRGBATexture(fallbackPixels, 2, 2);
}

// Adds a texture to be observed by the pool while also buffering it to the GPU. Callers are responsible for keeping the returned pointer alive.
std::shared_ptr<Texture>  TexturePool::Add(unsigned int texHash, textureType textype, const unsigned char* data, int width, int height)
{
	if (cache.find(texHash) == cache.end()) {
		std::shared_ptr<Texture> buffer = std::make_shared<Texture>(textype);
		buffer->genRGBATexture(data, width, height);
		cache.insert({texHash, buffer});
		return buffer;
	} else {
		std::cerr << "Attempted to add a texture whose texHash already exists: " << texHash << std::endl;
		// I chose to make this error case obvious.
		++errorTexInstances;
		return errorTex;
	}
}

// Checks if the hash exists in the cache, also checks if the stored pointer has expired and deletes it. 
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
    auto it = cache.find(texHash);
    if (it != cache.end()) {
        std::shared_ptr<Texture> tex = it->second.lock();
        if (tex)
            return tex;          // present and alive
    }
    std::cerr << "Tried to get a Texture with an invalid texHash: " << texHash << std::endl;
    ++errorTexInstances;
    return errorTex;
}
