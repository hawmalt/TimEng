#pragma once

#include "InputManager.h"
#include "Window.h"

#include <memory>
#include <string>

namespace TimEng{

	class IMainGame;
	class RenderingEngine;

	class CoreEngine
	{
	public:
		CoreEngine(std::string windowTitle, int windowWidth, int windowHeight, unsigned int flags, IMainGame* game);
		~CoreEngine();

		void run();

		void onSDLEvent(SDL_Event& evnt);

		const float getFps() const {
			return m_fps;
		}

		RenderingEngine* getRenderingEngine() const { return m_renderingEngine.get(); }

	private:

		void checkInput();


		IMainGame* m_game;

		bool m_isRunning = false;
		float m_fps = 0.0f;

		int m_windowWidth;
		int m_windowHeight;
		unsigned int m_windowFlags;
		std::string m_windowTitle;

		std::unique_ptr<RenderingEngine> m_renderingEngine;
		std::unique_ptr<InputManager> m_inputManager = std::make_unique<InputManager>();
	};

}