#pragma once

#include "RenderingEngine.h"
#include "InputManager.h"

namespace TimEng{

	class GameObject;

	class GameComponent
	{
	public:
		GameComponent();
		~GameComponent();

		virtual void update() = 0;
		virtual void render(RenderingEngine* renderingEngine) = 0;
		virtual void input(InputManager* inputManager) = 0;

		void setParentGameObject(GameObject* gameObject);

	protected:
		GameObject* m_parentGameObject = nullptr;
	};

}