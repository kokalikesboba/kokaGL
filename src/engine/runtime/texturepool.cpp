#include "texturepool.h"

TexturePool::TexturePool()
{
	
}

// While this adds to the texture cache, you are still responsible for generating the texture.
void TexturePool::Add(unsigned int hash, textureType textype)
{
	std::shared_ptr<Texture> buffer = std::make_shared<Texture>(textype);
	map.insert({hash, buffer});
}

bool TexturePool::isCached(unsigned int hash)
{
	return map.find(hash) != map.end();
}
