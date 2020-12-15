#include <iostream>
#include <SDL2/SDL.h>

#include "GameLoop.h"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

GameLoop::GameLoop() 
: renderer("TEST", SCREEN_WIDTH, SCREEN_HEIGHT, render_events_queue) { 
	// TODO: Agregar ServerEventsReceiver a la MIL
}

GameLoop::~GameLoop() {
	SDL_Quit();
}

void GameLoop::run() {
	// this->serverEventsReceiver.start();
	this->render_events_queue.push(START);
	this->renderer.start();

	SDL_Event user_event;
	while (true) {
		SDL_PollEvent(&(user_event));
		if (user_event.type == SDL_QUIT) break;
		// poll event, encolarlo, etc.
	}
}
