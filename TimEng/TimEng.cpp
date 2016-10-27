#include <SDL/SDL.h>
#include <GLEW/GL/glew.h>

#include "TimEng.h"

namespace TimEng{
	int init(){
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}
