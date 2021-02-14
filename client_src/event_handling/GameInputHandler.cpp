#include "GameInputHandler.h"

GameInputHandler::GameInputHandler(ServerConnection& server_connection,
																	 BlockingQueue<MessageType>& message_queue)
// Todo: Sacar message_queue, que ServerConnection haga los bloqueos
: server_connection(server_connection), message_queue(message_queue) { }

GameInputHandler::~GameInputHandler() { }

void GameInputHandler::handle(SDL_Event input) {
	if (input.key.repeat == 0) {
		MessageType type;
		switch (input.type) {
		case (SDL_KEYDOWN) : 
			switch (input.key.keysym.sym)
			{
			case SDLK_w:
				if (!this->keyboard_state.isDown(SDLK_w)) type = TYPE_MOVE_FORWARD_START;
				break;
			case SDLK_a:
				if (!this->keyboard_state.isDown(SDLK_a)) type = TYPE_MOVE_LEFT_START;
				break;
			case SDLK_s:
				if (!this->keyboard_state.isDown(SDLK_s)) type = TYPE_MOVE_BACKWARD_START;
				break;
			case SDLK_d:
				if (!this->keyboard_state.isDown(SDLK_d)) type = TYPE_MOVE_RIGHT_START;
				break;
			case SDLK_p:
				if (!this->keyboard_state.isDown(SDLK_p)) type = TYPE_SHOOT_START;
				break;
			default:
				type = TYPE_UNDEFINED_KEY;
				break;
			}
			this->message_queue.push(type);
		  	this->keyboard_state.toggleKeyDown(input.key.keysym.sym);
		  	break;
		case (SDL_KEYUP) :
			switch (input.key.keysym.sym )
			{
			case SDLK_w:
				if (this->keyboard_state.isDown(SDLK_w)) type = TYPE_MOVE_FORWARD_STOP;
				break;
			case SDLK_a:
				if (this->keyboard_state.isDown(SDLK_a)) type = TYPE_MOVE_LEFT_STOP;
				break;
			case SDLK_s:
				if (this->keyboard_state.isDown(SDLK_s)) type = TYPE_MOVE_BACKWARD_STOP;
				break;
			case SDLK_d:
				if (this->keyboard_state.isDown(SDLK_d)) type = TYPE_MOVE_RIGHT_STOP;
				break;
			case SDLK_p:
				if (this->keyboard_state.isDown(SDLK_p)) type = TYPE_SHOOT_STOP;
				break;
			default:
				type = TYPE_UNDEFINED_KEY;
				break;
			}
			this->message_queue.push(type); 
		  	this->keyboard_state.toggleKeyUp(input.key.keysym.sym);
		  	break;
	  	}
  
    }
  
	/*std::vector<MessageType> events;
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
	}*/	
}
