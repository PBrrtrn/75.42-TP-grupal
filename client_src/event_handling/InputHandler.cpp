#include <iostream>
#include "InputHandler.h"

#include "../enums/UpdateType.h"

InputHandler::InputHandler(std::atomic<bool>& in_game, 
													 UpdateQueue& update_queue,
													 ServerConnection& server_connection,
													 BlockingQueue<MessageType>& blockingQueue)
: in_game(in_game), menu_input_handler(update_queue),
	game_input_handler(server_connection,blockingQueue) { }

InputHandler::~InputHandler() { }

void InputHandler::process(SDL_Event user_event) {
	if (this->in_game) {
		this->game_input_handler.handle(user_event);
	} else {
		this->menu_input_handler.handle(user_event);
	}
}
