#include "GameInputHandler.h"

GameInputHandler::GameInputHandler(ServerConnection& server_connection,
																	 BlockingQueue<MessageType>& message_queue)
// Todo: Sacar message_queue, que ServerConnection haga los bloqueos
: server_connection(server_connection), message_queue(message_queue) { }

GameInputHandler::~GameInputHandler() { }

void GameInputHandler::handle(SDL_Event input) {
	switch (input.type) {
    case (SDL_KEYDOWN) : 
      this->keyboard_state.toggleKeyDown(input.key.keysym.sym);
      break;
    case (SDL_KEYUP) :
      this->keyboard_state.toggleKeyUp(input.key.keysym.sym);
      break;
  }
  
	std::vector<MessageType> events;
	if (this->keyboard_state.isDown(SDLK_w)){
		MessageType type = TYPE_MOVE_FORWARD;
		this->message_queue.push(type);
	}
	if (this->keyboard_state.isDown(SDLK_a)){
		MessageType type = TYPE_MOVE_LEFT;
		this->message_queue.push(type);
	}
	if (this->keyboard_state.isDown(SDLK_s)){
		MessageType type = TYPE_MOVE_BACKWARD;
		this->message_queue.push(type);
	}
	if (this->keyboard_state.isDown(SDLK_d)){
		MessageType type = TYPE_MOVE_RIGHT;
		this->message_queue.push(type);
	}	
}
