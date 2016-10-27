
#include <TimEng/IMainGame.h>
#include <TimEng/CoreEngine.h>

#include "App.h"

int main(int argc, char** argv){
	TimEng::CoreEngine core("WindowTitle", 800, 600, 0, new App());
	core.run();
	return 0;
}