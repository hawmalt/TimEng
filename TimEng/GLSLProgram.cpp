#include "GLSLProgram.h"

#include "TimEngErrors.h"
#include "IOManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <regex>


namespace TimEng{
	GLSLProgram::GLSLProgram() :_numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
		
		std::string vertSource;
		std::string fragSource;
		
		IOManager::readFileToBuffer(vertexShaderFilePath, vertSource);
		IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource);

		preprocessShader(vertSource);
		preprocessShader(fragSource);

		compileShadersFromSource(vertSource.c_str(), fragSource.c_str());

		addAllAttributes(vertSource);

	}

	void GLSLProgram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource){
		_programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		if (_vertexShaderID == 0){
			fatalError("Vertex Shader failed to be created");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		if (_fragmentShaderID == 0){
			fatalError("Fragment Shader failed to be created");
		}



		compileShader(vertexSource, "Vertex Shader", _vertexShaderID);
		compileShader(fragmentSource, "Fragment Shader", _fragmentShaderID);
	}

	void GLSLProgram::linkShaders() {

		//Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);



			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			//print the error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	void GLSLProgram::addAttribute(const std::string& attributeName){
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName){
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());

		if (location == GL_INVALID_INDEX){
			fatalError("Uniform " + uniformName + " not found in shader");
		}

		return location;
	}

	void GLSLProgram::use(){
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++){
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse(){
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++){
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::compileShader(const char* source, const std::string& name, GLuint id){
		
		glShaderSource(id, 1, &source, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Provide the infolog in whatever manor you deem best.
			//Exit with failure.
			glDeleteShader(id); //Don't leak the shader.

			//Print error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + name + " failed to compile");
		}
	}

	void GLSLProgram::preprocessShader(std::string& source){
		std::stringstream commentstream(source);

		std::getline(commentstream, source, '\0');
		//Get rid of comments
		while (source.find("//") != std::string::npos) {
			size_t Beg = source.find("//");
			source.erase(Beg, source.find("\n", Beg) - Beg);
		}
	
		std::regex comment("/\\*.*?\\*/");
		source = std::regex_replace(source, comment, "");
	}

	void GLSLProgram::addAllAttributes(const std::string& shaderCode){
		const std::string ATTRIBUTE_WORD = "in";

		std::stringstream stream(shaderCode);

		std::string inKeyword;
		std::string attributeName;
		std::string attributeType;

		while (stream >> inKeyword){
			
			if (inKeyword.compare(ATTRIBUTE_WORD) == 0){
				stream >> attributeType >> attributeName;
				attributeName.pop_back();

				addAttribute(attributeName);
			}
		}

	}

}