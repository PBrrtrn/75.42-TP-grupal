#ifndef __STATUS_UPDATER_H__
#define __STATUS_UPDATER_H__

#include <atomic>

#include "UpdateQueue.h"
#include "MenuStatusUpdater.h"
#include "GameStatusUpdater.h"
#include "../game_status/MenuStatus.h"
#include "../game_status/GameStatusMonitor.h"
#include "../ServerConnection.h"
#include "../../common_src/Thread.h"

class StatusUpdater : public Thread {
private:
	std::atomic<bool>& in_game;
	MenuStatusUpdater menu_status_updater;
	GameStatusUpdater game_status_updater;
public:
	StatusUpdater(std::atomic<bool>& in_game,
								UpdateQueue& update_queue,
								ServerConnection& server_connection,
								MenuStatus& menu_status,
								GameStatusMonitor& game_status_monitor,
								BlockingQueue<MessageType>& blockingQueue);
	~StatusUpdater();
	void run();
};

#endif
