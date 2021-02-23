#ifndef __GAME_INPUT_HANDLER_H__
#define __GAME_INPUT_HANDLER_H__

#include <SDL2/SDL.h>

#include "KeyboardState.h"
#include "../../common_src/blocking_queue.h"
#include "../../common_src/ClientMessage.h"

class GameInputHandler {
private:
	KeyboardState keyboard_state;
	BlockingQueue<ClientMessage>& message_queue;
public:
	GameInputHandler(BlockingQueue<ClientMessage>& message_queue);
	~GameInputHandler();
	void handle(SDL_Event user_input);
};

#endif
