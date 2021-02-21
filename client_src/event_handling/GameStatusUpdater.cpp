#include "GameStatusUpdater.h"

GameStatusUpdater::GameStatusUpdater(GameStatusMonitor& game_status_monitor,
                                     ServerConnection& server_connection) 
: game_status_monitor(game_status_monitor),
	server_connection(server_connection),
  has_map(false) { }

GameStatusUpdater::~GameStatusUpdater() { }

void GameStatusUpdater::updateStatus() { 	
	if (!this->has_map) {
		Map map = this->server_connection.fetchMap();
		this->game_status_monitor.initializeMap(map);
		this->has_map = true;
		this->server_connection.sendPing();
	}
	
	GameStatusUpdate update;
	GameStatistics statistics;
	MessageType message = this->server_connection.receiveIncomingEvent();
	switch (message) {
		case (TYPE_SERVER_SEND_GAME_UPDATE) :
			update = this->server_connection.getGameStatusUpdate();
			this->game_status_monitor.updateGameStatus(update);
			break;
		case (TYPE_SERVER_SEND_GAME_STATISTICS) :
			statistics = this->server_connection.receiveStatistics();
			// Hacer algo con las estadísticas
			break;
	}
	
	/*
	std::vector<MessageType> events;
	
	this->message_queue.lock();
	while (!this->message_queue.isEmptySync()) {
		MessageType message = this->message_queue.popSync();
		events.push_back(message);
	}
	this->message_queue.unlock();
	
	this->server_connection.sendEvents(events);
	*/
}
