#include "UpdateReceiver.h"

UpdateReceiver::UpdateReceiver(std::atomic<bool>& in_game, 
								ServerConnection& connection,
								GameStatusMonitor& game_status_monitor,
								MenuStatus& menu_status,
								std::atomic<bool>& end_game)
: in_game(in_game), connection(connection),
	game_status_monitor(game_status_monitor), menu_status(menu_status),
	end_game(end_game) { }

UpdateReceiver::~UpdateReceiver() {
	this->join();
}

void UpdateReceiver::run() {
	while (true) {
		MessageType message_type = this->connection.receiveMessageType();
		if (this->in_game || this->end_game) this->receiveGameUpdate(message_type);
		else if (!this->in_game && !this->end_game)this->receiveMenuUpdate(message_type);
	}
}

void UpdateReceiver::receiveGameUpdate(MessageType message_type) {
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
	this->in_game = false;
	this->end_game = true;
	GameStatistics statistics = this->connection.getGameStatistics();
	this->game_status_monitor.saveStatistics(statistics);
}

void UpdateReceiver::receiveMenuUpdate(MessageType message_type) {
	switch (message_type) {
		case (TYPE_SERVER_SEND_MAP_LIST) :
			this->fetchMapOptions();
			break;
		case (TYPE_SERVER_SEND_GAMES_LIST) :
			this->fetchGameOptions();
			break;
		case (TYPE_SERVER_JOIN_OK) :
			this->menu_status.updateCurrentScreen(LOBBY);
			break;
		case (TYPE_LOBBY_STATUS_UPDATE) :
			this->fetchLobbyStatus();
			break;
		case (TYPE_SERVER_SEND_GAME_UPDATE) :
			this->fetchGameUpdate();
			break;
	}
}

void UpdateReceiver::fetchMapOptions() {
	std::vector<MapListItem> maps = this->connection.getMapOptions();
	this->menu_status.updateMapOptions(maps);
}

void UpdateReceiver::fetchGameOptions() {
	std::vector<GameListItem> games = this->connection.getGameOptions();
	this->menu_status.updateGameOptions(games);
}

void UpdateReceiver::fetchLobbyStatus() {
	LobbyStatusData lobby_status = this->connection.getLobbyStatus();
	this->menu_status.updateLobbyStatus(lobby_status);
	if (lobby_status.gameStarted)
		this->in_game = true;
	if (lobby_status.remainingTime == 0)
		this->menu_status.updateCurrentScreen(GAME_CREATION);
	// this->menu_status.updateLobbyStatus(lobby_status);
}
