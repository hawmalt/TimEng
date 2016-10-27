#include "CoreEngine.h"
#include "Timing.h"

#include "IMainGame.h"
#include "RenderingEngine.h"

namespace TimEng{
	CoreEngine::CoreEngine(std::string windowTitle, int windowWidth, int windowHeight, unsigned int flags, IMainGame* game) : 
		m_game(game),
		m_windowWidth(windowWidth),
		m_windowHeight(windowHeight),
		m_windowFlags(flags),
		m_windowTitle(windowTitle)
	{
		m_renderingEngine = std::make_unique<RenderingEngine>();
	}


	CoreEngine::~CoreEngine()
	{
	}

	void CoreEngine::onSDLEvent(SDL_Event& evnt){
		switch (evnt.type) {
		case SDL_QUIT:
			m_game->exitGame();
			m_isRunning = false;
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.get()->setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.get()->pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.get()->releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.get()->pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.get()->releaseKey(evnt.button.button);
			break;
		}
	}

	void CoreEngine::run(){

		TimEng::init();

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		m_renderingEngine->createWindow(m_windowTitle, m_windowWidth, m_windowHeight, m_windowFlags);

		m_game->setCoreEngine(this);

		m_game->init();

		FpsLimiter limiter;
		limiter.setMaxFPS(m_fps);

		m_isRunning = true;
		while (m_isRunning){
			limiter.begin();

			m_inputManager.get()->update();

			checkInput();

			m_game->input(m_inputManager.get());
			m_game->update();
			m_renderingEngine->render(m_game);


			m_fps = limiter.end();
		}

	}
	

	void CoreEngine::checkInput(){
		SDL_Event evnt;

		while (SDL_PollEvent(&evnt)){
			onSDLEvent(evnt);
		}
	}
}