#ifndef __GAME_STATUS_UPDATER_H__
#define __GAME_STATUS_UPDATER_H__

#include "../game_status/GameStatusMonitor.h"
#include "../ServerConnection.h"

class GameStatusUpdater {
private:
	bool hasMap;
	GameStatusMonitor& game_status_monitor;
	ServerConnection& server_connection;
public:
	GameStatusUpdater(GameStatusMonitor& game_status_monitor,
										ServerConnection& server_connection);
	~GameStatusUpdater();
	void updateStatus();
};

#endif
