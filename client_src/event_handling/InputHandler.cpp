#include <iostream>
#include "InputHandler.h"

InputHandler::InputHandler(std::atomic<bool>& in_game, MenuStatus& menu_status,
							BlockingQueue<ClientMessage>& message_queue, 
							std::atomic<bool>& end_game)
: in_game(in_game), menu_input_handler(message_queue, menu_status),
	game_input_handler(message_queue), end_game(end_game) { }

InputHandler::~InputHandler() { }

void InputHandler::process(SDL_Event user_input) {
	if (this->in_game) {
		this->game_input_handler.handle(user_input);
	} else if (!this->in_game && !this->end_game){
		this->menu_input_handler.handle(user_input);
	}
}
