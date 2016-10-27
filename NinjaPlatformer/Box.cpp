#include "Box.h"
#include <TimEng/ResourceManager.h>
#include <TimEng/GameObject.h>

#include <SDL/SDL.h>


Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World* world, const glm::vec2& position, const glm::vec2& dimentions, TimEng::ColorRGBA8 color){
	m_dimentions = dimentions;
	m_color = color;
	m_texture = TimEng::ResourceManager::getTexture("Assets/bricks_top.png");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);

	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimentions.x / 2.0f, dimentions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Box::update(){
	
}

void Box::render(TimEng::RenderingEngine* renderingEngine){

	m_parentGameObject->setPositionAndDimentions(glm::vec4(m_body->GetPosition().x - getDimentions().x / 2.0f,
		m_body->GetPosition().y - getDimentions().y / 2.0f,
		getDimentions().x,
		getDimentions().y));

	m_parentGameObject->setAngle(m_body->GetAngle());

	GLint textureUniform = renderingEngine->getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	renderingEngine->draw(m_parentGameObject->getPositionAndDimentions(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture.id, 0.0f, m_color, m_parentGameObject->getAngle());

}

void Box::input(TimEng::InputManager* inputManager){
	float SPEED = 15.0f;
	if (inputManager->isKeyDown(SDLK_w)){
		float xvel = SPEED * cos(m_body->GetAngle());
		float yvel = SPEED * sin(m_body->GetAngle());
		m_body->ApplyForceToCenter(b2Vec2(xvel, yvel), true);
	}
	else if (inputManager->isKeyDown(SDLK_s)){
		float xvel = -SPEED * cos(m_body->GetAngle());
		float yvel = -SPEED * sin(m_body->GetAngle());
		m_body->ApplyForceToCenter(b2Vec2(xvel, yvel), true);
	}
	if (inputManager->isKeyDown(SDLK_a)){
		m_body->ApplyTorque(5.0f, true);
	}
	else if (inputManager->isKeyDown(SDLK_d)){
		m_body->ApplyTorque(-5.0f, true);
	}
}