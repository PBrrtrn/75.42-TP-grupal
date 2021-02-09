#include "GameStatusUpdater.h"

GameStatusUpdater::GameStatusUpdater(GameStatusMonitor& game_status_monitor,
																		 ServerConnection& server_connection) 
: game_status_monitor(game_status_monitor), 
	server_connection(server_connection)  { 
		this->hasMap = false;
	}

GameStatusUpdater::~GameStatusUpdater() { }

void GameStatusUpdater::updateStatus() { 
	
	
	if (!this->hasMap) {
		std::cout << "voy a obtener el mapa" << std::endl;
		this->server_connection.fetchMap();
		std::cout << "obtuve el mapa" << std::endl;
		this->hasMap = true;
	}
	
	
	
	//while (true) {
	this->server_connection.fetchGameStatusUpdate();
	this->server_connection.sendPing();
		
		//}
	
	}
