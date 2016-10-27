#include "ResourceManager.h"

namespace TimEng{
	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(std::string filePath){
		return _textureCache.getTexture(filePath);
	}
}