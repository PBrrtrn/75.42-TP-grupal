#include "MenuInputHandler.h"

MenuInputHandler::MenuInputHandler(BlockingQueue<Request>& request_queue,
																	 MenuStatus& menu_status)
: request_queue(request_queue) {
	Request request { TYPE_CLIENT_REQUEST_MAPS_LIST }
	this->request_queue.push(request);
	this->refresh();
}

MenuInputHandler::~MenuInputHandler() { }

void MenuInputHandler::handle(SDL_Event input) {
	if (input.type == SDL_KEYDOWN) {
		Screen current_screen = this->menu_status.getCurrentScreen();
		switch (current_screen) {
			case (GAME_SELECTION) :
				handleGameSelection(input);
				break;
			case (LOBBY) :
				handleLobby(input);
				break;
			case (GAME_CREATION) :
				handleGameCreation(input);
				break;
		}
	}
}

void MenuInputHandler::handleGameSelection(SDL_Event input) {
	int selected_option = this->menu_status.getSelectedOption();
	SDL_Keycode keycode = input.key.keysym.sym;

	if (keycode == SDLK_SPACE) {
		if (selected_option == 0) {
			this->menu_status.updateCurrentScreen(START_GAME);
		}	else if (selected_option == 1) {
			this->refresh();
		} else {
			std::vector<GameListItem> options = this->menu_status.getGameOptions();
		}
	} else {
		// Mover la opcion seleccionada
	}

}

void MenuInputHandler::handleLobby(SDL_Event input) {
	if (input.key.keysym.sym == SDLK_SPACE)
		// Pushear evento para pedir salir del lobby
}

void MenuInputHandler::handleGameCreation(SDL_Event input) {
}

void MenuInputHandler::refresh() {
	Request request { TYPE_CLIENT_REQUEST_GAMES_LIST };
	this->request_queue.push(request);
}

/*
void MenuInputHandler::handle(std::vector<SDL_Event>& inputs) {
	for (auto input : inputs) {
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
}
*/