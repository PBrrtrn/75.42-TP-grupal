#ifndef __GAME_INPUT_HANDLER_H__
#define __GAME_INPUT_HANDLER_H__

#include <SDL2/SDL.h>

#include "KeyboardState.h"
#include "../ServerConnection.h"

class GameInputHandler {
private:
	KeyboardState keyboard_state;
	ServerConnection& server_connection;
public:
	GameInputHandler(ServerConnection& server_connection);
	~GameInputHandler();
	void handle(SDL_Event input);
};

#endif