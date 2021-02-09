#ifndef __GAME_STATUS_UPDATER_H__
#define __GAME_STATUS_UPDATER_H__

#include "../game_status/GameStatusMonitor.h"
#include "../ServerConnection.h"
#include "../../common_src/blocking_queue.h"

class GameStatusUpdater {
private:
	GameStatusMonitor& game_status_monitor;
	ServerConnection& server_connection;
	BlockingQueue<MessageType>& message_queue;
	bool has_map;
public:
	GameStatusUpdater(GameStatusMonitor& game_status_monitor,
										ServerConnection& server_connection,
										BlockingQueue<MessageType>& message_queue);
	~GameStatusUpdater();
	void updateStatus();
};

#endif
