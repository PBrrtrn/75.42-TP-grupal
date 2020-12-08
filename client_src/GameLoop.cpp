#include <iostream>
#include <SDL2/SDL.h>

#include "GameLoop.h"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

GameLoop::GameLoop() 
: renderer("TEST", SCREEN_WIDTH, SCREEN_HEIGHT, render_events_queue) { 
	// TODO: Agregar ServerEventsReceiver a la MIL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		throw SDLInitializationError(SDL_GetError());
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		std::cout << "Warning: Could not set render scale quality" << std::endl;
}

GameLoop::~GameLoop() {
	SDL_Quit();
}

void GameLoop::run() {
	// this->serverEventsReceiver.start();
	this->renderer.start();
}

SDLInitializationError::SDLInitializationError
								(const char *sdl_error) noexcept {
	snprintf(this->error_msg, ERROR_BUF_LEN, 
					 "Failed to initialize SDL: %s", sdl_error);
}

SDLInitializationError::~SDLInitializationError() noexcept { }

const char* SDLInitializationError::what() const noexcept {
	return this->error_msg;
}
