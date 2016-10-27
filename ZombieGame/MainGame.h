#pragma once

#include <TimEng/Window.h>
#include <TimEng/GLSLProgram.h>
#include <TimEng/Camera2D.h>
#include <TimEng/InputManager.h>
#include <TimEng/SpriteBatch.h>
#include <TimEng/SpriteFont.h>
#include <TimEng/AudioEngine.h>
#include <TimEng/ParticleEngine2D.h>
#include <TimEng/ParticleBatch2D.h>

#include "Player.h"
#include "Level.h"
#include "Bullet.h"

class Zombie;

enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();

	/// Initializes the level and sets up everything
	void initLevel();

	/// Initializes the shaders
	void initShaders();

	/// Main game loop for the program
	void gameLoop();

	/// Updates all agents
	void updateAgents(float deltaTime);

	/// Updates all bullets
	void updateBullets(float deltaTim);

	/// Checks the victory condition
	void checkVictory();

	/// Handles input processing
	void processInput();

	/// Renders the game
	void drawGame();

	/// Draws the HUD
	void drawHud();

	/// Adds blood to the particle engine
	void addBlood(const glm::vec2& position, int numParticles);

	/// Member Variables
	TimEng::Window m_window; ///< The game window

	TimEng::GLSLProgram m_textureProgram; ///< The shader program

	TimEng::InputManager m_inputManager; ///< Handles input

	TimEng::Camera2D m_camera; ///< Main Camera
	TimEng::Camera2D m_hudCamera; ///< Hud Camera

	TimEng::SpriteBatch m_agentSpriteBatch; ///< Draws all agents
	TimEng::SpriteBatch m_hudSpriteBatch;

	TimEng::ParticleEngine2D m_particleEngine;
	TimEng::ParticleBatch2D* m_bloodParticleBatch;

	std::vector<Level*> m_levels; ///< vector of all levels

	int m_screenWidth = 1024;
	int m_screenHeight = 768;

	float m_fps;

	int m_currentLevel;

	Player* m_player;
	std::vector<Human*> m_humans; ///< Vector of all humans
	std::vector<Zombie*> m_zombies; ///< Vector of all zombies
	std::vector<Bullet> m_bullets;

	int m_numHumansKilled; ///< Humans killed by player
	int m_numZombiesKilled; ///< Zombies killed by player

	TimEng::SpriteFont* m_spriteFont;

	TimEng::AudioEngine m_audioEngine;

	GameState m_gameState;
};

