#include "UpdateReceiver.h"

UpdateReceiver::UpdateReceiver(std::atomic<bool>& in_game, 
								 							 ServerConnection& connection,
								 							 GameStatusMonitor& game_status_monitor,
								 							 MenuStatus& menu_status)
: in_game(in_game), connection(connection),
	game_status_monitor(game_status_monitor), menu_status(menu_status) { }

UpdateReceiver::~UpdateReceiver() {
	this->join();
}

void UpdateReceiver::run() {
	while (true) {
		MessageType message_type = this->connection.receiveMessageType();
		if (this->in_game) this->receiveGameUpdate(message_type);
		else this->receiveMenuUpdate(message_type);
	}
}

void UpdateReceiver::receiveGameUpdate(MessageType message_type) {
	std::cout << "receive Game Update" << std::endl;
	switch (message_type) {
		case (TYPE_SERVER_SEND_MAP) :
			this->fetchMap();
			break;
		case (TYPE_SERVER_SEND_GAME_UPDATE) :
			this->fetchGameUpdate();
			break;
		case (TYPE_SERVER_SEND_GAME_STATISTICS) :
			this->fetchStatistics();
			break;
	}
}

void UpdateReceiver::fetchMap() {
	Map map = this->connection.getMap();
	this->game_status_monitor.initializeMap(map);
}

void UpdateReceiver::fetchGameUpdate() {
	GameStatusUpdate update = this->connection.getGameStatusUpdate();
	this->game_status_monitor.updateGameStatus(update);
}

void UpdateReceiver::fetchStatistics() {
	GameStatistics statistics = this->connection.getGameStatistics();
	// Hacer algo con las statistics
}

void UpdateReceiver::receiveMenuUpdate(MessageType message_type) {
	std::cout << "receive Menu Update:"<< message_type << std::endl;
	switch (message_type) {
		case (TYPE_SERVER_SEND_MAP_LIST) :
			std::cout << "receive map list" << std::endl;
			this->fetchMapOptions();
			break;
		case (TYPE_SERVER_SEND_GAMES_LIST) :
			std::cout << "receive games list" << std::endl;
			this->fetchGameOptions();
			break;
		case (TYPE_SERVER_JOIN_OK) :
			std::cout << "receive join ok" << std::endl;
			this->menu_status.updateCurrentScreen(LOBBY);
			break;
		case (TYPE_LOBBY_STATUS_UPDATE) :
			std::cout << "receive lobby status" << std::endl;
			this->fetchLobbyStatus();
			break;
		case (TYPE_SERVER_SEND_GAME_UPDATE) :
			std::cout << "receive game update (menu update)" << std::endl;
			/*esto no deberia ser necesario, pero fetchLobbyStatus no esta leyendo el valor de gameStarted correctamente!*/
			this->fetchGameUpdate();
			this->in_game = true;
			break;
	}
}

void UpdateReceiver::fetchMapOptions() {
	std::cout << "Updating map options in menu status" << std::endl;
	std::vector<MapListItem> maps = this->connection.getMapOptions();
	this->menu_status.updateMapOptions(maps);
}

void UpdateReceiver::fetchGameOptions() {
	std::vector<GameListItem> games =  this->connection.getGameOptions();
	this->menu_status.updateGameOptions(games);
}

void UpdateReceiver::fetchLobbyStatus() {
	LobbyStatusData lobby_status = this->connection.getLobbyStatus();
	if (lobby_status.gameStarted){
		std::cout << "game started!" << std::endl;
		in_game = true;
	}
	// this->menu_status.updateLobbyStatus(lobby_status);
}
