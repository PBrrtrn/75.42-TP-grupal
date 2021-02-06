#include <iostream>
#include "InputHandler.h"

#include "../enums/UpdateType.h"

InputHandler::InputHandler(std::atomic<bool>& in_game, 
													 UpdateQueue& update_queue)
: in_game(in_game), update_queue(update_queue) { }

InputHandler::~InputHandler() { }

void InputHandler::process(SDL_Event user_event) {
	// TODO: Mappear controles en config
	if (this->in_game) {
		switch (user_event.type) {
      case (SDL_KEYDOWN) : 
        this->keyboard_state.toggleKeyDown(user_event.key.keysym.sym);
        break;
      case (SDL_KEYUP) :
        this->keyboard_state.toggleKeyUp(user_event.key.keysym.sym);
        break;
    }
    // Procesar keyboard_state y enviar evento por socket
	} else if (user_event.type == SDL_KEYDOWN) {
		switch (user_event.key.keysym.sym) {
			case (SDLK_w) :
				std::cout << "pressed W" << std::endl;
				this->update_queue.pushUpdate(MENU_MOVE_UP);
				break;
			case (SDLK_s) :
				std::cout << "pressed S" << std::endl;
				this->update_queue.pushUpdate(MENU_MOVE_DOWN);
				break;
			case (SDLK_SPACE) :
				std::cout << "pressed Spacebar" << std::endl;
				this->update_queue.pushUpdate(MENU_SELECT_OPTION);
				break;
		}
	}
}