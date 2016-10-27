#include "IMainGame.h"
#include "Timing.h"

#include "ScreenList.h"
#include "IGameScreen.h"
#include "RenderingEngine.h"

namespace TimEng{
	IMainGame::IMainGame()
	{
		m_screenList = std::make_unique <ScreenList> ();
	}


	IMainGame::~IMainGame()
	{
	}


	void IMainGame::exitGame(){
		m_currentScreen->onExit();

		if (m_screenList){
			m_screenList->destroy();
			m_screenList.reset();
		}
	}

	void IMainGame::init(){
		onInit();
		addScreens();

		m_currentScreen = m_screenList->getCurrent();
		m_currentScreen->onEntry();
		m_currentScreen->setUpShaders(m_coreEngine->getRenderingEngine());
		m_currentScreen->setRunning();
	}

	void IMainGame::update(){
		if (m_currentScreen){
			switch (m_currentScreen->getState()){
			case ScreenState::RUNNING:
				m_currentScreen->update();
				m_currentScreen->getRootObject()->update();
				break;
			case ScreenState::CHANGE_NEXT:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveNext();
				if (m_currentScreen){
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
					m_currentScreen->setUpShaders(m_coreEngine->getRenderingEngine());

				}
				break;
			case ScreenState::CHANGE_PREVIOUS:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->movePrevious();
				if (m_currentScreen){
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
					m_currentScreen->setUpShaders(m_coreEngine->getRenderingEngine());

				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exitGame();
				break;
			default:
				break;
			}
		}
		else{
			exitGame();
		}
	}
	
	void IMainGame::draw(RenderingEngine* renderingEngine){

		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING){
			m_currentScreen->draw(renderingEngine);
			m_currentScreen->getRootObject()->render(renderingEngine);
		}
	}

	void IMainGame::input(InputManager* inputManager){
		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING){
			m_currentScreen->input(inputManager);
			m_currentScreen->getRootObject()->input(inputManager);
		}
	}

}