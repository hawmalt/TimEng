#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

namespace TimEng{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string filePath){
		std::map<std::string, GLTexture>::iterator mit = _textureMap.find(filePath);

		if (mit == _textureMap.end()){
			GLTexture newTexture = ImageLoader::loadPNG(filePath);

			_textureMap.insert(make_pair(filePath, newTexture));
			return newTexture;
		}
		return mit->second;
	}
}