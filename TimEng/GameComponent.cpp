#include "GameComponent.h"

#include "GameObject.h"

namespace TimEng{
	GameComponent::GameComponent()
	{
	}


	GameComponent::~GameComponent()
	{
	}

	void GameComponent::setParentGameObject(GameObject* gameObject){
		m_parentGameObject = gameObject;
	}

}