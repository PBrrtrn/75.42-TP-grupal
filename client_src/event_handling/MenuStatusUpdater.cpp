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

	/* opcion 0 esta reservada para host game, opcion 1 para refrescar*/
	if (update == MENU_SELECT_OPTION) {
		if (selected_option == 0) {
			this->menu_status.updateCurrentScreen(START_GAME);
		} else if (selected_option == 1) {
			refresh();
		} else {
			// Pedir al server que te agregue a la partida
			/*si pidieron entrar a un juego, index = opcion - 2 */
			//this->in_game = 
			

			
			if (!this->server_connection.joinGame(games.at(selected_option - 2).gameId)) {
			std::cout << "entre al juego! GameId:" << games.at(selected_option - 2).gameId << std::endl;	
				LobbyStatusData l;
				l.gameStarted = false;
				MessageType message;
				message = TYPE_LOBBY_STATUS_UPDATE;
				
				while (message == TYPE_LOBBY_STATUS_UPDATE) {
					
					std::cout << "voy a recibir un incoming event" << std::endl;
					
					MessageType message = this->server_connection.receiveIncomingEvent();
					
					std::cout << "llego un incoming event:" << message << std::endl;
					
					this->server_connection.sendPing();
					
					if (message == TYPE_LOBBY_STATUS_UPDATE) {
						std::cout << "hay que entrar a lobby update" << std::endl;
						l = this->server_connection.fetchLobbyStatus();	
					}
					if (message == TYPE_SERVER_SEND_MAP) {
						std::cout << "hay que salir del menu e ir a obtener el mapa" << std::endl;
						break;
					}					
					
					
					//else {
					//	std::cout << "ya empezo el juego" << std::endl;
					//	l.gameStarted = true;
						
					//}
				}
				//std::cout << "hay que obtener el mapa" << std::endl;
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
