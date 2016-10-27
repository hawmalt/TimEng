#include "Level.h"

#include <fstream>
#include <iostream>
#include <TimEng/TimEngErrors.h>

#include <TimEng/ResourceManager.h>


Level::Level(const std::string& fileName)
{
	std::ifstream file;

	file.open(fileName);

	if (file.fail()){
		TimEng::fatalError("Failed to open " + fileName);
	}
	std::string tmp;
	file >> tmp >> _numHumans;

	std::getline(file, tmp);
	while (std::getline(file, tmp)){
		_levelData.push_back(tmp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	TimEng::ColorRGBA8 whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	for (int y = 0; y < _levelData.size(); y++){
		for (int x = 0; x < _levelData[y].size(); x++){
			char tile = _levelData[y][x];

			//get dest rect
			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile){
			case 'B':
			case 'R':
				_spriteBatch.draw(
					destRect, 
					uvRect, 
					TimEng::ResourceManager::getTexture("Textures/red_bricks.png").id, 
					0.0f,
					whiteColor);
				break;
			case 'G':
				_spriteBatch.draw(
					destRect,
					uvRect,
					TimEng::ResourceManager::getTexture("Textures/glass.png").id,
					0.0f,
					whiteColor);
				break;
			case 'L':
				_spriteBatch.draw(
					destRect,
					uvRect,
					TimEng::ResourceManager::getTexture("Textures/light_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case '@':
				_levelData[y][x] = '.';
				_startPlayerPos.x = x*TILE_WIDTH;
				_startPlayerPos.y = y*TILE_WIDTH;
				break;
			case 'Z':
				_levelData[y][x] = '.';
				_zombieStartPos.emplace_back(x*TILE_WIDTH, y*TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				std::cout << "Unexpected tile " << tile << " at " << x << " " << y << std::endl;
				break;
			}
		}
	}

	_spriteBatch.end();
}


Level::~Level()
{
}

void Level::draw(){
	_spriteBatch.renderBatch();
}

