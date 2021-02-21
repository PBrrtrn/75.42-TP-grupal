#include <iostream>
#include "InputHandler.h"

InputHandler::InputHandler(std::atomic<bool>& in_game, MenuStatus& menu_status,
							 						 BlockingQueue<Request>& request_queue)
: in_game(in_game), menu_input_handler(request_queue, menu_status),
	game_input_handler(request_queue) { }

InputHandler::~InputHandler() { }

void InputHandler::process(SDL_Event user_input) {
	if (this->in_game) {
		this->game_input_handler.handle(user_input);
	} else {
		this->menu_input_handler.handle(user_input);
	}
}
