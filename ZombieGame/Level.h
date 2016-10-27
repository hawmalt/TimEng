#pragma once

#include <string>
#include <vector>

#include <TimEng/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	Level(const std::string& fileName);
	~Level();

	void draw();

	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getZombieStartPositions() const { return _zombieStartPos; }
	const std::vector<std::string>& getLevelData() const { return _levelData; }
	int getNumHumans() const { return _numHumans; }
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }

private:
	std::vector<std::string> _levelData;
	int _numHumans;
	TimEng::SpriteBatch _spriteBatch;

	glm::vec2 _startPlayerPos;

	std::vector<glm::vec2> _zombieStartPos;
};

