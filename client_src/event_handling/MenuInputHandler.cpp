#include "MenuInputHandler.h"

MenuInputHandler::MenuInputHandler(UpdateQueue& update_queue)
: update_queue(update_queue) { }

MenuInputHandler::~MenuInputHandler() { }

void MenuInputHandler::handle(SDL_Event input) {
	if (input.type == SDL_KEYDOWN) {
		switch (input.key.keysym.sym) {
			case (SDLK_w) :
				this->update_queue.pushUpdate(MENU_MOVE_UP);
				break;
			case (SDLK_s) :
				this->update_queue.pushUpdate(MENU_MOVE_DOWN);
				break;
			case (SDLK_SPACE) :
				this->update_queue.pushUpdate(MENU_SELECT_OPTION);
				break;
		}
	}
}