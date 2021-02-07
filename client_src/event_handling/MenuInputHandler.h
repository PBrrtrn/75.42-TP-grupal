#ifndef __MENU_INPUT_HANDLER_H__
#define __MENU_INPUT_HANDLER_H__

#include <SDL2/SDL.h>

#include "UpdateQueue.h"

class MenuInputHandler {
private:
	UpdateQueue& update_queue;
public:
	MenuInputHandler(UpdateQueue& update_queue);
	~MenuInputHandler();
	void handle(SDL_Event input);
};

#endif