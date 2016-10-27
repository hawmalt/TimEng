#pragma once

#include <glm.hpp>
#include <TimEng/SpriteBatch.h>

const float AGENT_WIDTH = 60;
const float AGENT_RADIUS = (float)AGENT_WIDTH / 2;

class Zombie;
class Human;


class Agent
{
public:
	Agent();
	virtual ~Agent();

	void draw(TimEng::SpriteBatch& spriteBatch);

	bool applyDamage(float damage);

	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies,
						float deltaTime) = 0;

	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool collideWithAgent(Agent* agent);

	glm::vec2 getPosition() const { return _position; }

protected:
	void checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y);
	void collideWithTile(glm::vec2 tilePos);

	glm::vec2 _position;
	glm::vec2 m_direction = glm::vec2(1.0f, 0.0f);
	TimEng::ColorRGBA8 _color;
	float _speed;
	float _health;

	GLuint m_textureID;
};

