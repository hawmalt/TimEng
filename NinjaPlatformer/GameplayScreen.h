#pragma once

#include <TimEng/IGameScreen.h>
#include <Box2D/Box2D.h>
#include <TimEng/RenderingEngine.h>
#include <TimEng/InputManager.h>
#include <TimEng/Camera2D.h>

#include <memory>
#include <vector>

#include "Box.h"


class GameplayScreen : public TimEng::IGameScreen
{
public:
	GameplayScreen();
	~GameplayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
	virtual void draw(TimEng::RenderingEngine* renderingEngine) override;
	virtual void input(TimEng::InputManager* inputManager) override;


	virtual void setUpShaders(TimEng::RenderingEngine* renderingEngine) override;


private:
	std::unique_ptr < b2World > m_world;
	TimEng::Camera2D* m_camera;
};

