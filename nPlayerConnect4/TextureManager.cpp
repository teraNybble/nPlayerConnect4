#include "TextureManager.h"
#include "ImageLoder.h"

void TextureManager::loadTex(const char* path)
{
	textures.push_back(ImageLoder::loadPNG(path));
}