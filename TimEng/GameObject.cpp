#include "GameObject.h"

#include "GameComponent.h"
#include "RenderingEngine.h"

namespace TimEng{
	GameObject::GameObject()
	{
	}


	GameObject::~GameObject()
	{
	}

	void GameObject::addChild(GameObject* gameObject){
		m_children.push_back(gameObject);
		gameObject->setParentGameObject(this);
	}

	void GameObject::addComponent(GameComponent* gameComponent){
		m_components.push_back(gameComponent);
		gameComponent->setParentGameObject(this);
	}

	void GameObject::update(){

		for (GameComponent* c : m_components){
			c->update();
		}

		for (GameObject* g : m_children){
			g->update();
		}
	}

	void GameObject::render(RenderingEngine* renderingEngine){

		for (GameComponent* c : m_components){
			c->render(renderingEngine);
		}

		for (GameObject* g : m_children){
			g->render(renderingEngine);
		}
	}

	void GameObject::input(InputManager* inputManager){
		for (GameComponent* c : m_components){
			c->input(inputManager);
		}

		for (GameObject* g : m_children){
			g->input(inputManager);
		}
	}

}