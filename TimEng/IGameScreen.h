#pragma once

#define SCREEN_INDEX_NO_SCREEN -1

#include "GameObject.h"
#include "RenderingEngine.h"
#include "InputManager.h"

#include <memory>

namespace TimEng{

	class IMainGame;

	enum class ScreenState{
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};

	class IGameScreen
	{
	public:
		friend class ScreenList;

		IGameScreen(){

		}
		virtual ~IGameScreen(){

		}
		

		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;

		virtual void build() = 0;
		virtual void destroy() = 0;

		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		virtual void update() = 0;
		virtual void draw(RenderingEngine* renderingEngine) = 0;
		virtual void input(InputManager* renderingEngine) = 0;

		virtual void setUpShaders(RenderingEngine* renderingEngine) = 0;


		int getScreenIndex() const { return m_screenIndex; }

		void setRunning(){ m_currentState = ScreenState::RUNNING; }

		ScreenState getState() const { return m_currentState; }

		GameObject* getRootObject(){ return m_rootObject.get(); }

		void addGameObject(GameObject* gameObject){ m_rootObject.get()->addChild(gameObject); }


	protected:
		ScreenState m_currentState = ScreenState::NONE;

		std::unique_ptr<GameObject> m_rootObject = std::make_unique<GameObject>();

		int m_screenIndex = SCREEN_INDEX_NO_SCREEN;
	};

}