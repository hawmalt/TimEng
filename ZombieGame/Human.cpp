#include "Human.h"
#include <ctime>
#include <random>
#include<gtx/rotate_vector.hpp>
#include <TimEng/ResourceManager.h>

Human::Human() : _frames(0)
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos){
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

	_health = 20;

	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;

	_speed = speed;
	_position = pos;
	m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (m_direction.length() == 0){
		m_direction = glm::vec2(1.0f, 0.0f);
	}

	m_direction = glm::normalize(m_direction);
	m_textureID = TimEng::ResourceManager::getTexture("Textures/human.png").id;
}

void Human::update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies,
					float deltaTime){

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);

	_position += m_direction * _speed * deltaTime;

	if (_frames == 20){
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
		_frames = 0;
	}
	else{
		_frames++;
	}

	if (collideWithLevel(levelData)){
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
	}
}