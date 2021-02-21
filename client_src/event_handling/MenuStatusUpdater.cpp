#include <iostream>

#include "MenuStatusUpdater.h"

MenuStatusUpdater::MenuStatusUpdater(UpdateQueue& update_queue, 
																		 MenuStatus& menu_status,
																		 ServerConnection& server_connection,
																		 std::atomic<bool>& in_game)
: menu_status(menu_status), update_queue(update_queue),
	server_connection(server_connection), in_game(in_game) {
	this->refresh();

	std::vector<MapListItem> maps = this->server_connection.fetchAvailableMaps();
	this->menu_status.updateMapOptions(maps);
}

MenuStatusUpdater::~MenuStatusUpdater() { }

void MenuStatusUpdater::updateStatus() {
	int selected_option = this->menu_status.getSelectedOption();
	UpdateType update = this->update_queue.popUpdate();
	// Puede que haya que actualizar popUpdate() para que traiga un vector de UpdateType? 

	if (this->menu_status.getCurrentScreen() == LOBBY) {
		handleLobbyScreen(selected_option, update);
	} else {
		handleStartGameScreen(selected_option, update);
	}
}

void MenuStatusUpdater::handleStartGameScreen(int selected_option, 
																							UpdateType update) {
	std::vector<MapListItem> maps = this->menu_status.getMapOptions();

	if (update == MENU_SELECT_OPTION) {
		if (selected_option == 0) {
			this->menu_status.updateCurrentScreen(LOBBY);
		} else {
			// Pedir empezar un juego con ese mapa
		}
	} else {
		int n_options = maps.size() + 1;
		int move_direction = ((update == MENU_MOVE_UP) ? 1 : -1);
		// updatear selected_option a new_selection como en handleLobbyScreen
	}
}

void MenuStatusUpdater::handleLobbyScreen(int selected_option,
																					UpdateType update) {
	std::vector<GameListItem> games = this->menu_status.getGameOptions();

	if (update == MENU_SELECT_OPTION) {
		if (selected_option == 0) {
			// (selected_option == 0) -> HOST NEW
			this->menu_status.updateCurrentScreen(START_GAME);
		} else if (selected_option == 1) {
			// (selected_option == 1) -> REFRESH
			refresh();
		} else {
			// Pedir al server que te agregue a la partida
			if (!this->server_connection.joinGame(games[selected_option - 2].gameId)) {
				LobbyStatusData lobby_status;
				lobby_status.gameStarted = false;
				MessageType message;
				message = TYPE_LOBBY_STATUS_UPDATE;
				
				while (message == TYPE_LOBBY_STATUS_UPDATE) {
					MessageType message = this->server_connection.receiveIncomingEvent();
					this->server_connection.sendPing();
					
					if (message == TYPE_LOBBY_STATUS_UPDATE) {
						lobby_status = this->server_connection.fetchLobbyStatus();	
					}
					if (message == TYPE_SERVER_SEND_MAP) {
						break;
					}			
				}
				this->in_game = true;
			}
		}
	} else {
		int n_options = games.size() + 2;
		int move_direction = ((update == MENU_MOVE_UP) ? 1 : -1);
		int new_selection = (selected_option + move_direction) % n_options;
		if (new_selection < 0) new_selection = - new_selection;

		this->menu_status.updateSelectedOption(new_selection);
	}
}

void MenuStatusUpdater::refresh() {
	std::vector<GameListItem> games = this->server_connection.fetchGameOptions();
	this->menu_status.updateGameOptions(games);
}
