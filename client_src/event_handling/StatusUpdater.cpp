#include <iostream>
#include "StatusUpdater.h"

#include "../enums/UpdateType.h"

StatusUpdater::StatusUpdater(std::atomic<bool>& in_game,
														 UpdateQueue& update_queue,
														 ServerConnection& server_connection,
														 MenuStatus& menu_status,
														 GameStatusMonitor& game_status_monitor)
: in_game(in_game), 
	menu_status_updater(update_queue, menu_status, server_connection, in_game),
	game_status_updater(game_status_monitor, server_connection) { }

StatusUpdater::~StatusUpdater() {
	this->join();
}

void StatusUpdater::run() {
	while (true) {
		if (this->in_game) this->game_status_updater.updateStatus();
		else this->menu_status_updater.updateStatus();
	}
}
