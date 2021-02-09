#include "GameStatusUpdater.h"

GameStatusUpdater::GameStatusUpdater(GameStatusMonitor& game_status_monitor,
						ServerConnection& server_connection,BlockingQueue<MessageType>& blockingQueue) 
: game_status_monitor(game_status_monitor), 
	server_connection(server_connection),
	blockingQueue(blockingQueue)  { 
		this->hasMap = false;
	}

GameStatusUpdater::~GameStatusUpdater() { }

void GameStatusUpdater::updateStatus() { 
	
	
	if (!this->hasMap) {
		std::cout << "voy a obtener el mapa" << std::endl;
		Map map = this->server_connection.fetchMap();
		std::cout << "obtuve el mapa" << std::endl;
		this->game_status_monitor.initializeMap(map);
		this->hasMap = true;
		this->server_connection.sendPing();
	}
	
	GameStatusUpdate gsu = this->server_connection.fetchGameStatusUpdate();
	
	this->game_status_monitor.updateGameStatus(gsu);
	std::vector<MessageType> events;
	
	this->blockingQueue.lock();
	while (!this->blockingQueue.isEmptySync()) {
		MessageType mt = this->blockingQueue.popSync();
		events.push_back(mt);
	}
	this->blockingQueue.unlock();
	
	this->server_connection.sendEvents(events);

	
	}
