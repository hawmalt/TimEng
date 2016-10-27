#pragma once

#include "GLTexture.h"
#include <string>

namespace TimEng{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}
