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
}