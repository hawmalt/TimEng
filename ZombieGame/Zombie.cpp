#include "Zombie.h"

#include <TimEng/ResourceManager.h>

#include "Human.h"

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos){
	_health = 150;
	_speed = speed;
	_position = pos;
	_color = TimEng::ColorRGBA8(255, 255, 255, 255);
	m_textureID = TimEng::ResourceManager::getTexture("Textures/zombie.png").id;
}

void Zombie::update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies,
					float deltaTime){

	Human* closestHuman = getNearestHuman(humans);
	if (closestHuman != nullptr){
		m_direction = glm::normalize(closestHuman->getPosition() - _position);
		_position += m_direction * _speed * deltaTime;
	}

	collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans){
	Human* closestHuman = nullptr;
	float smallestDistance = 999999999.0f;

	for (int i = 0; i < humans.size(); i++){
		glm::vec2 distVec = humans[i]->getPosition() - _position;
		float distance = glm::length(distVec);

		if (distance < smallestDistance){
			closestHuman = humans[i];
			smallestDistance = distance;
		}
	}

	return closestHuman;
}