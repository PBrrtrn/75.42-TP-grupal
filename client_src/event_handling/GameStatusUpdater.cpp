#include "GameStatusUpdater.h"

GameStatusUpdater::GameStatusUpdater(GameStatusMonitor& game_status_monitor,
																		 ServerConnection& server_connection) 
: game_status_monitor(game_status_monitor), 
	server_connection(server_connection)  { }

GameStatusUpdater::~GameStatusUpdater() { }

void GameStatusUpdater::updateStatus() { }