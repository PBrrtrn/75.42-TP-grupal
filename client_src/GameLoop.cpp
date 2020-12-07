#include <SDL2/SDL.h>

#include "GameLoop.h"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

GameLoop::GameLoop()
: renderEventsQueue(), serverEventsReceiver(renderEventsQueue) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) throw 1;
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		std::cout << "Warning: Could not set render scale quality" << std::endl;
}

GameLoop::GameLoop() {
	SDL_Quit();
}

void GameLoop::run() {
	serverEventsReceiver.start();

	bool running;
}
