#ifndef __GAME_INPUT_HANDLER_H__
#define __GAME_INPUT_HANDLER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_mixer.h>
//#include "SDL_mixer.h"
//#include "SDL_mixer.dll"

#include "KeyboardState.h"
#include "../ServerConnection.h"
#include "../../common_src/blocking_queue.h"

class GameInputHandler {
private:
	KeyboardState keyboard_state;
	ServerConnection& server_connection;
	BlockingQueue<MessageType>& message_queue;
public:
	GameInputHandler(ServerConnection& server_connection,
									 BlockingQueue<MessageType>& message_queue);
	~GameInputHandler();
	void handle(SDL_Event input);
};

#endif
