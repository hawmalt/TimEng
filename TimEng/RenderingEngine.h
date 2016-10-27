#pragma once

#include "GLSLProgram.h"
#include "SpriteBatch.h"
#include "Window.h"
#include "Camera2D.h"
#include "SpriteFont.h"

#include <glm/glm.hpp>
#include "Vertex.h"

namespace TimEng{

	class IMainGame;
	class RenderingEngine
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		void createWindow(std::string windowTitle, int windowWidth, int windowHeight, unsigned int flags);

		void render(IMainGame* mainGame);

		void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
			GLuint texture, float depth, const ColorRGBA8& color);

		void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
			GLuint texture, float depth, const ColorRGBA8& color, float angle);

		void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
			GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir);

		void drawText(SpriteFont spriteFont, const char* s, glm::vec2 position, glm::vec2 scaling,
			float depth, ColorRGBA8 tint, Justification just = Justification::LEFT);

		GLuint getUniformLocation(std::string uniformName){ return m_glslProgram->getUniformLocation(uniformName); }
		Window* getWindow(){ return &m_window; }

		Camera2D* makeCamera(); //TODO: Can cause memory leaks change the camera creation system

		void setGLSLProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void setGLSLProgramFromSource(const char* vertexSource, const char* fragmentSource);
		
	private:
		SpriteBatch* m_spriteBatch = nullptr;
		GLSLProgram* m_glslProgram = nullptr;

		Window m_window;
	};

}