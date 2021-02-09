#include "GameInputHandler.h"

GameInputHandler::GameInputHandler(ServerConnection& server_connection)
: server_connection(server_connection) { }

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
	std::cout << "en manejo de eventos" << std::endl;
  
	std::vector<MessageType> events;
	if (this->keyboard_state.isDown(SDLK_w)){
		MessageType type = TYPE_MOVE_FORWARD;
		events.push_back(type);
		std::cout << "evento adelante" << std::endl;
	}
	if (this->keyboard_state.isDown(SDLK_a)){
		MessageType type = TYPE_MOVE_LEFT;
		events.push_back(type);
	}
	if (this->keyboard_state.isDown(SDLK_s)){
		MessageType type = TYPE_MOVE_BACKWARD;
		events.push_back(type);
		std::cout << "evento atras" << std::endl;
	}
	if (this->keyboard_state.isDown(SDLK_d)){
		MessageType type = TYPE_MOVE_RIGHT;
		events.push_back(type);
	}	
	
	this->server_connection.sendEvents(events);
	
  
}
