#include <iostream>
#include "InputHandler.h"

#include "../enums/UpdateType.h"

InputHandler::InputHandler(std::atomic<bool>& in_game, 
	UpdateQueue& update_queue, ServerConnection& server_connection,
	BlockingQueue<MessageType>& blockingQueue) : 
	in_game(in_game), 
	menu_input_handler(update_queue),
	game_input_handler(server_connection,blockingQueue) 
	{ 
		if (SDL_Init(SDL_INIT_AUDIO) < 0) {
			printf("Error SDL audio initialization: %s\n", SDL_GetError()); 
		}

		if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
			printf("Error SDL_mixer initialization %s\n", Mix_GetError());
		}
}


void InputHandler::process(SDL_Event user_event) {
	if (this->in_game) {
		this->game_input_handler.handle(user_event);
	} else {
		this->menu_input_handler.handle(user_event);
	}
}

InputHandler::~InputHandler() { }
