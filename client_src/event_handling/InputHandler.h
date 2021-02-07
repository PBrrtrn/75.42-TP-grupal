#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <atomic>
#include <SDL2/SDL.h>

#include "UpdateQueue.h"
#include "MenuInputHandler.h"
#include "GameInputHandler.h"
#include "../ServerConnection.h"

class InputHandler {
private:
	std::atomic<bool>& in_game;
	MenuInputHandler menu_input_handler;
	GameInputHandler game_input_handler;
public:
	InputHandler(std::atomic<bool>& in_game, 
							 UpdateQueue& update_queue,
							 ServerConnection& server_connection);
	~InputHandler();
	void process(SDL_Event user_event);
};

#endif