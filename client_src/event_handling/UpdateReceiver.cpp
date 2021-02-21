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
	switch (message_type) {
		case (TYPE_SERVER_SEND_MAP) :
			Map map = this->connection.getMap();
			this->game_status_monitor.initializeMap(map);
			break;
		case (TYPE_SERVER_SEND_GAME_UPDATE) :
			GameStatusUpdate update = this->connection.getGameStatusUpdate();
			this->game_status_monitor.updateGameStatus(update);
			break;
		case (TYPE_SERVER_SEND_GAME_STATISTICS) :
			GameStatistics statistics = this->connection.getGameStatistics();
			break;
	}
}

void UpdateReceiver::receiveMenuUpdate(MessageType message_type) {
	switch (message_type) {
		case (TYPE_SERVER_SEND_MAP_LIST) :
			std::vector<MapListItem> maps = this->connection.getMapOptions();
			this->menu_status.updateMapOptions(maps);
			break;
		case (TYPE_SERVER_SEND_GAMES_LIST) :
			std::vector<GameListItem> games =  this->connection.getGameOptions();
			this->menu_status.updateGameOptions(games);
			break;
		case (TYPE_SERVER_JOIN_OK) :
			// this->menu_status.updateCurrentScreen(LOBBY);
		case (TYPE_LOBBY_STATUS_UPDATE) :
			LobbyStatusData lobby_status = this->connection.getLobbyStatus();
			if (lobby_status.gameStarted) in_game = true;
			// this->menu_status
			break;
	}
}