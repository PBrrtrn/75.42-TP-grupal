#include "GameStatusUpdater.h"

GameStatusUpdater::GameStatusUpdater(GameStatusMonitor& game_status_monitor,
																		 ServerConnection& server_connection,
																		 BlockingQueue<MessageType>& message_queue) 
: game_status_monitor(game_status_monitor), server_connection(server_connection),
	message_queue(message_queue), has_map(false) { }

GameStatusUpdater::~GameStatusUpdater() { }

void GameStatusUpdater::updateStatus() { 	
	if (!this->has_map) {
		Map map = this->server_connection.fetchMap();
		this->game_status_monitor.initializeMap(map);
		this->has_map = true;
		this->server_connection.sendPing();
	}
	
	GameStatusUpdate update = this->server_connection.fetchGameStatusUpdate();
	
	this->game_status_monitor.updateGameStatus(update);
	std::vector<MessageType> events;
	
	this->message_queue.lock();
	while (!this->message_queue.isEmptySync()) {
		MessageType message = this->message_queue.popSync();
		events.push_back(message);
	}
	this->message_queue.unlock();
	
	this->server_connection.sendEvents(events);

	
	}
