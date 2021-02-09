#ifndef __GAME_INPUT_HANDLER_H__
#define __GAME_INPUT_HANDLER_H__

#include <SDL2/SDL.h>

#include "KeyboardState.h"
#include "../ServerConnection.h"
#include "../../common_src/blocking_queue.h"

class GameInputHandler {
private:
	KeyboardState keyboard_state;
	ServerConnection& server_connection;
	BlockingQueue<MessageType>& blockingQueue;
public:
	GameInputHandler(ServerConnection& server_connection, BlockingQueue<MessageType>& blockingQueue);
	~GameInputHandler();
	void handle(SDL_Event input);
};

#endif
