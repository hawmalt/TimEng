#pragma once

#include <TimEng/Vertex.h>
#include <TimEng/GameComponent.h>
#include <TimEng/RenderingEngine.h>
#include <TimEng/InputManager.h>
#include <TimEng/GLTexture.h>

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

class Box : public TimEng::GameComponent
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimentions, TimEng::ColorRGBA8 color);

	virtual void update() override;
	virtual void render(TimEng::RenderingEngine* renderingEngine) override;
	virtual void input(TimEng::InputManager* inputManager) override;

	b2Body* getBody() const { return m_body; }
	b2Fixture* getFixture() const { return m_fixture; }
	const glm::vec2& getDimentions() const { return m_dimentions; }
	const TimEng::ColorRGBA8& getColor() const { return m_color; }

private:
	TimEng::GLTexture m_texture;

	b2Body* m_body = nullptr;
	b2Fixture* m_fixture = nullptr;
	glm::vec2 m_dimentions;
	TimEng::ColorRGBA8 m_color;
};

