#ifndef __MENU_INPUT_HANDLER_H__
#define __MENU_INPUT_HANDLER_H__

#include <SDL2/SDL.h>

#include "../game_status/MenuStatus.h"
#include "../../common_src/blocking_queue.h"
#include "../../common_src/ClientMessage.h"

class MenuInputHandler {
private:
	BlockingQueue<ClientMessage>& message_queue;
	MenuStatus& menu_status;
	void handleGameSelection(SDL_Event input);
	void handleLobby(SDL_Event input);
	void handleGameCreation(SDL_Event input);
	void refresh();
public:
	MenuInputHandler(BlockingQueue<ClientMessage>& message_queue, 
									 MenuStatus& menu_status);
	~MenuInputHandler();
	void handle(SDL_Event user_input);
};

#endif