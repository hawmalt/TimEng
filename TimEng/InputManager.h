#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace TimEng{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		bool isKeyDown(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);

		void setMouseCoords(float x, float y);

		glm::vec2 getMouseCoords() const { return _mouseCoords; }

	private:
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map <unsigned int, bool> _keyMap;
		std::unordered_map <unsigned int, bool> _previousKeyMap;

		glm::vec2 _mouseCoords;
	};

}