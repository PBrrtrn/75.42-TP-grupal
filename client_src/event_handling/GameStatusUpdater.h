#ifndef __GAME_STATUS_UPDATER_H__
#define __GAME_STATUS_UPDATER_H__

#include "../game_status/GameStatusMonitor.h"
#include "../ServerConnection.h"
#include "../../common_src/blocking_queue.h"

class GameStatusUpdater {
private:
	bool hasMap;
	GameStatusMonitor& game_status_monitor;
	ServerConnection& server_connection;
	BlockingQueue<MessageType>& blockingQueue;
public:
	GameStatusUpdater(GameStatusMonitor& game_status_monitor,
										ServerConnection& server_connection,BlockingQueue<MessageType>& blockingQueue);
	~GameStatusUpdater();
	void updateStatus();
};

#endif
