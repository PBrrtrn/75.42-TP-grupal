#include "MenuInputHandler.h"

MenuInputHandler::MenuInputHandler(UpdateQueue& update_queue)
: update_queue(update_queue) { }

void MenuInputHandler::handle(SDL_Event input) {
	if (input.type == SDL_KEYDOWN) {
		switch (input.key.keysym.sym) {
			case (SDLK_w) :
				this->update_queue.pushUpdate(MENU_MOVE_UP);
				this->_playSound("/home/laptop-hp/Documentos/FACULTAD/Taller de programación I/tp final/SERVER/75.42-TP-grupal/client_src/sound_effects/SOUNDS/M_MOVE.wav", 0);
				break;
			case (SDLK_s) :
				this->update_queue.pushUpdate(MENU_MOVE_DOWN);
				this->_playSound("/home/laptop-hp/Documentos/FACULTAD/Taller de programación I/tp final/SERVER/75.42-TP-grupal/client_src/sound_effects/SOUNDS/M_MOVE.wav", 0);
				break;
			case (SDLK_SPACE) :
				this->update_queue.pushUpdate(MENU_SELECT_OPTION);
				this->_playSound("/home/laptop-hp/Documentos/FACULTAD/Taller de programación I/tp final/SERVER/75.42-TP-grupal/client_src/sound_effects/SOUNDS/M_SELECT.wav", 0);
				break;
		}
	}
}

void MenuInputHandler::_playSound(const char* path, int loops) {
	int channel; 
	this->sound = Mix_LoadWAV(path);
	if (this->sound == NULL) printf("Loading sound error: %s\n", Mix_GetError());
	channel = Mix_PlayChannel(-1, this->sound, loops); 
}

MenuInputHandler::~MenuInputHandler() { }