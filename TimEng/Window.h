#pragma once

#include <SDL/SDL.h>
#include <GLEW/GL/glew.h>
#include <string>

namespace TimEng{
	enum WindowFlags{
		INVISABLE = 0x1,
		FULLSCREEN = 0x2,
		BOARDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		int getScreenWidth(){ return m_screenWidth; }
		int getScreenHeight(){ return m_screenHeight; }

		void swapBuffer();

	private:
		SDL_Window* _sdlWindow;
		int m_screenWidth = 0;
		int m_screenHeight = 0;
	};

}