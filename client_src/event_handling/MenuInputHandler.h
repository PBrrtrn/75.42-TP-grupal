#ifndef __MENU_INPUT_HANDLER_H__
#define __MENU_INPUT_HANDLER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "UpdateQueue.h"

class MenuInputHandler {
private:
	UpdateQueue& update_queue;
	Mix_Chunk *sound;
	void _playSound(const char* path, int loops);
public:
	MenuInputHandler(UpdateQueue& update_queue);
	~MenuInputHandler();
	void handle(SDL_Event input);
};

#endif