#include "GameInputHandler.h"

const SDL_Keycode mapped_keys[] = { SDLK_w, SDLK_a, SDLK_s, SDLK_d };

GameInputHandler::GameInputHandler(ServerConnection& server_connection,
																	 BlockingQueue<MessageType>& message_queue)
// Todo: Sacar message_queue, que ServerConnection haga los bloqueos
: server_connection(server_connection), message_queue(message_queue) { }

GameInputHandler::~GameInputHandler() { }

void GameInputHandler::handle(SDL_Event input) {
	if (input.key.repeat == 0) {
		SDL_Keycode keycode = input.key.keysym.sym;
		if (input.type == SDL_KEYDOWN) {
			if (!this->keyboard_state.isDown(keycode)) {
				switch (keycode) {
					case (SDLK_w) : 
						this->message_queue.push(TYPE_MOVE_FORWARD_START);
						break;
					case (SDLK_a) : 
						this->message_queue.push(TYPE_MOVE_LEFT_START);
						break;
					case (SDLK_s) : 
						this->message_queue.push(TYPE_MOVE_BACKWARD_START);
						break;
					case (SDLK_d) : 
						this->message_queue.push(TYPE_MOVE_RIGHT_START);
						break;
				}
			}
		  this->keyboard_state.toggleKeyDown(keycode);
		} else {
			if (this->keyboard_state.isDown(keycode)) {
				switch (keycode) {
					case (SDLK_w) : 
						this->message_queue.push(TYPE_MOVE_FORWARD_STOP);
						break;
					case (SDLK_a) : 
						this->message_queue.push(TYPE_MOVE_LEFT_STOP);
						break;
					case (SDLK_s) : 
						this->message_queue.push(TYPE_MOVE_BACKWARD_STOP);
						break;
					case (SDLK_d) : 
						this->message_queue.push(TYPE_MOVE_RIGHT_STOP);
						break;
				}
			}
		  this->keyboard_state.toggleKeyUp(keycode);
		}
  }
}
