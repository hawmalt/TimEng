#pragma once

#include <string>
#include <glm.hpp>
#include <vector>
#include "Bullet.h"
#include <TimEng/AudioEngine.h>

class Gun
{
public:
	Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed, TimEng::SoundEffect fireEffect);
	~Gun();

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);

private:

	TimEng::SoundEffect m_fireEffect;

	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets);

	std::string _name;

	int _fireRate;
	int _bulletsPerShot;
	float _spread;

	float _bulletSpeed;
	float _bulletDamage;

	float _frameCounter;

};

