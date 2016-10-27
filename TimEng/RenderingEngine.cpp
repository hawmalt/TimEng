#include "RenderingEngine.h"

#include "IMainGame.h"

namespace TimEng{
	RenderingEngine::RenderingEngine()
	{
	}


	RenderingEngine::~RenderingEngine()
	{
	}

	void RenderingEngine::createWindow(std::string windowTitle, int windowWidth, int windowHeight, unsigned int flags){
		m_window.create(windowTitle, windowWidth, windowHeight, flags);
	}

	void RenderingEngine::render(IMainGame* mainGame){

		glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());

		if (m_spriteBatch == nullptr){
			m_spriteBatch = new SpriteBatch();
			m_spriteBatch->init();
		}

		m_glslProgram->use();

		m_spriteBatch->begin();
		
		mainGame->draw(this);

		m_spriteBatch->end();
		m_spriteBatch->renderBatch();

		m_glslProgram->unuse();

		m_window.swapBuffer();
	}


	void RenderingEngine::draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
		GLuint texture, float depth, const ColorRGBA8& color){
		m_spriteBatch->draw(destinationRectangle, uvRectangle,
			texture, depth, color);
	}

	void RenderingEngine::draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
		GLuint texture, float depth, const ColorRGBA8& color, float angle){
		m_spriteBatch->draw(destinationRectangle, uvRectangle,
			texture, depth, color, angle);
	}

	void RenderingEngine::draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
		GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir){
		m_spriteBatch->draw(destinationRectangle, uvRectangle,
			texture, depth, color, dir);
	}

	void RenderingEngine::drawText(SpriteFont spriteFont, const char* s, glm::vec2 position, glm::vec2 scaling,
		float depth, ColorRGBA8 tint, Justification just){
		spriteFont.draw(*m_spriteBatch, s, position, scaling, depth, tint, just);
	}

	Camera2D* RenderingEngine::makeCamera(){
		Camera2D* cam = new Camera2D();
		cam->init(m_window.getScreenWidth(), m_window.getScreenHeight());
		return cam;
	}

	void RenderingEngine::setGLSLProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){

		if (m_glslProgram != nullptr){
			delete m_glslProgram;
		}

		m_glslProgram = new GLSLProgram();
		m_glslProgram->compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
		m_glslProgram->linkShaders();
	}

	void RenderingEngine::setGLSLProgramFromSource(const char* vertexSource, const char* fragmentSource){
		if (m_glslProgram != nullptr){
			delete m_glslProgram;
		}

		m_glslProgram = new GLSLProgram();
		m_glslProgram->compileShadersFromSource(vertexSource, fragmentSource);
		m_glslProgram->linkShaders();
	}
}