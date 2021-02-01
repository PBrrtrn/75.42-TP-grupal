#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <atomic>
#include <SDL2/SDL.h>

#include "KeyboardState.h"
#include "InputQueue.h"

class InputHandler {
private:
	std::atomic<bool>& in_game;
	UpdateQueue& update_queue;
	KeyboardState keyboard_state;
public:
	InputHandler(std::atomic<bool>& in_game, UpdateQueue& update_queue);
	~InputHandler();
	void process(SDL_Event event);
}

#endif