#pragma once

#include "TimEng.h"
#include "CoreEngine.h"
#include "InputManager.h"

#include <memory>

namespace TimEng{

	class ScreenList;
	class IGameScreen;
	class RenderingEngine;

	class IMainGame
	{
	public:
		friend class CoreEngine;
		friend class RenderingEngine;

		IMainGame();
		virtual ~IMainGame();

		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;


		const void setCoreEngine(CoreEngine* coreEngine){ m_coreEngine = coreEngine; }
		void init();

	protected:
		void update();
		void draw(RenderingEngine* renderingEngine);
		void input(InputManager* inputManager);

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_currentScreen = nullptr;
		CoreEngine* m_coreEngine;
	};

}