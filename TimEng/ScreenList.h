#pragma once

#include <vector>

#include "IGameScreen.h"

namespace TimEng{

	class IGameScreen;

	class ScreenList
	{
	public:
		ScreenList();
		~ScreenList();
		
		IGameScreen* moveNext();
		IGameScreen* movePrevious();

		void setScreen(int nextScreen);
		void addScreen(IGameScreen* newScreen);

		void destroy();

		IGameScreen* getCurrent();

	protected:
		std::vector<IGameScreen*> m_screens;
		int m_currentScreenIndex = SCREEN_INDEX_NO_SCREEN;
	};

}