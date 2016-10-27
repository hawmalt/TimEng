#include "GameplayScreen.h"

#include <TimEng/GLSLProgram.h>
#include <iostream>

#include <random>

#include "Box.h"

GameplayScreen::GameplayScreen()
{
}


GameplayScreen::~GameplayScreen()
{
}

int GameplayScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build(){

}

void GameplayScreen::destroy(){

}

void GameplayScreen::onEntry(){

	b2Vec2 gravity(0.0f, 0.0f);
	m_world = std::make_unique<b2World>(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -25.0f);
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-10.0, 10.0f);
	std::uniform_real_distribution<float> yPos(-10.0, 25.0f);
	std::uniform_real_distribution<float> size(0.5, 2.5f);
	std::uniform_int_distribution<int> color(50, 255);
	const int NUM_BOXES = 50;

	for (int i = 0; i < NUM_BOXES; i++){
		TimEng::GameObject* boxObject = new TimEng::GameObject();
		TimEng::ColorRGBA8 randColor;
		randColor.r = color(randGenerator);
		randColor.g = color(randGenerator);
		randColor.b = color(randGenerator);
		randColor.a = 255;
		Box* newBox = new Box();
		newBox->init(m_world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(size(randGenerator), size(randGenerator)), randColor);
		boxObject->addComponent(newBox);
		addGameObject(boxObject);
	}

}

void GameplayScreen::onExit(){

}

void GameplayScreen::update(){
	m_world->Step(1.0f/60.0f, 6, 2);
	m_camera->update();
}

void GameplayScreen::draw(TimEng::RenderingEngine* renderingEngine){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 projectionMatrix = m_camera->getCameraMatrix();
	GLint pUniform = renderingEngine->getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

}

void GameplayScreen::setUpShaders(TimEng::RenderingEngine* renderingEngine){
	renderingEngine->setGLSLProgram("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_camera = renderingEngine->makeCamera();
	m_camera->setScale(32.0f);
}

void GameplayScreen::input(TimEng::InputManager* inputManager){

}