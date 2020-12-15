#include <iostream>
#include <SDL2/SDL.h>

#include "GameLoop.h"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

GameLoop::GameLoop() 
: renderer("TEST", SCREEN_WIDTH, SCREEN_HEIGHT, render_events_queue) { 
	// IMPORTANTE: Estas creando el renderer antes de hacer SDL_Init, pavote
	// TODO: Agregar ServerEventsReceiver a la MIL
}

GameLoop::~GameLoop() {
	SDL_Quit();
}

void GameLoop::run() {
	// this->serverEventsReceiver.start();
	this->render_events_queue.push(START);
	this->renderer.start();
	while (true) {
		// poll event, encolarlo, etc.
	}
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
