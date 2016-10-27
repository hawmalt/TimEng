#pragma once

#include "TextureCache.h"
#include <string>

namespace TimEng{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string filePath);

	private:
		static TextureCache _textureCache;
	};

}