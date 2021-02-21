#ifndef __GAME_INPUT_HANDLER_H__
#define __GAME_INPUT_HANDLER_H__

#include <SDL2/SDL.h>

#include "KeyboardState.h"
#include "Request.h"
#include "../../common_src/blocking_queue.h"

class GameInputHandler {
private:
	KeyboardState keyboard_state;
	BlockingQueue<Request>& request_queue;
public:
	GameInputHandler(BlockingQueue<Request>& request_queue);
	~GameInputHandler();
	void handle(SDL_Event user_input);
};

#endif
