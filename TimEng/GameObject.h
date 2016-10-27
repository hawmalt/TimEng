#pragma once

#include <glm/glm.hpp>

#include "InputManager.h"

#include <vector>

namespace TimEng{

	class GameComponent;
	class RenderingEngine;

	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void addChild(GameObject* gameObject);
		void addComponent(GameComponent* gameComponent);

		void update();
		void render(RenderingEngine* renderingEngine);
		void input(InputManager* inputManager);

		const glm::vec4 getPositionAndDimentions() const { return m_positionAndDimentions; }
		const void setPositionAndDimentions(glm::vec4 const &posDim){ m_positionAndDimentions = posDim; }

		const float getAngle() const { return m_angle; }
		const void setAngle(float angle){ m_angle = angle; }

		const GameObject* getParentGameObject() const { return m_parentGameObject; }
		const void setParentGameObject(GameObject* const gameObject) { m_parentGameObject = gameObject; }

	private:
		GameObject* m_parentGameObject = nullptr;

		std::vector<GameObject*> m_children;
		std::vector<GameComponent*> m_components;

		glm::vec4 m_positionAndDimentions = glm::vec4(0.0f);
		float m_angle = 0.0f;
	};
}

