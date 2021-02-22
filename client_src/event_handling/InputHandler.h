#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <atomic>
#include <SDL2/SDL.h>

#include "MenuInputHandler.h"
#include "GameInputHandler.h"
#include "../game_status/MenuStatus.h"
#include "../../common_src/blocking_queue.h"
#include "../../common_src/ClientMessage.h"

class InputHandler {
private:
	std::atomic<bool>& in_game;
	MenuInputHandler menu_input_handler;
	GameInputHandler game_input_handler;
public:
	InputHandler(std::atomic<bool>& in_game, MenuStatus& menu_status,
							 BlockingQueue<ClientMessage>& message_queue);
	~InputHandler();
	void process(SDL_Event user_input);
};

#endif
