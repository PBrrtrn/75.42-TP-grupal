#include <iostream>
#include "MenuInputHandler.h"

MenuInputHandler::MenuInputHandler(BlockingQueue<Request>& request_queue,
																	 MenuStatus& menu_status)
: request_queue(request_queue), menu_status(menu_status) {
	Request request { CLIENT_REQUEST_MAPS_LIST };
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
			this->menu_status.updateCurrentScreen(GAME_CREATION);
		}	else if (selected_option == 1) {
			this->refresh();
		} else {
			std::vector<GameListItem> options = this->menu_status.getGameOptions();
			char game_id = options[selected_option - 2].gameId; 
			Request request { CLIENT_REQUEST_JOIN_GAME, game_id };
			this->request_queue.push(request);
		}
	} else if (keycode == SDLK_w) {
		this->menu_status.selectOptionUp();
	} else if (keycode == SDLK_s) {
		this->menu_status.selectOptionDown();
	}

}

void MenuInputHandler::handleLobby(SDL_Event input) {
	if (input.key.keysym.sym == SDLK_SPACE) {
		Request request { CLIENT_REQUEST_LEAVE_GAME };
		this->request_queue.push(request);
	}
}

void MenuInputHandler::handleGameCreation(SDL_Event input) {
	int selected_option = this->menu_status.getSelectedOption();
	SDL_Keycode keycode = input.key.keysym.sym;

	if (keycode == SDLK_SPACE) {
		if (selected_option == 0) {
			this->menu_status.updateCurrentScreen(GAME_SELECTION);
		} else {
			std::vector<MapListItem> options = this->menu_status.getMapOptions();
			char map_id = options[selected_option - 1].mapId; 
			Request request { CLIENT_REQUEST_CREATE_GAME, map_id };
			this->request_queue.push(request);
		}
	} else if (keycode == SDLK_w) {
		this->menu_status.selectOptionUp();
	} else if (keycode == SDLK_s) {
		this->menu_status.selectOptionDown();
	}
}

void MenuInputHandler::refresh() {
	Request request { CLIENT_REQUEST_GAMES_LIST };
	this->request_queue.push(request);
}
