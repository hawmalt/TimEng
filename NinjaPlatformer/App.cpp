#include "App.h"

#include <TimEng/ScreenList.h>

App::App()
{
}


App::~App()
{
}

void App::onInit(){
	//Load the Shaders
	
}

void App::addScreens(){
	m_gameplayScreen = std::make_unique < GameplayScreen >();

	m_screenList->addScreen(m_gameplayScreen.get());
	m_screenList->setScreen(m_gameplayScreen->getScreenIndex());
}

void App::onExit(){

}