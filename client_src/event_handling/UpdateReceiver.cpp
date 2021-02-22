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
	std::cout << "receive Menu Update" << std::endl;
	switch (message_type) {
		case (TYPE_SERVER_SEND_MAP_LIST) :
			this->fetchMapOptions();
			break;
		case (TYPE_SERVER_SEND_GAMES_LIST) :
			this->fetchGameOptions();
			break;
		case (TYPE_SERVER_JOIN_OK) :
			this->menu_status.updateCurrentScreen(LOBBY);
		case (TYPE_LOBBY_STATUS_UPDATE) :
			this->fetchLobbyStatus();
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
	if (lobby_status.gameStarted) in_game = true;
	// this->menu_status.updateLobbyStatus(lobby_status);
}
