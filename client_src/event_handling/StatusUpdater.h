#ifndef __STATUS_UPDATER_H__
#define __STATUS_UPDATER_H__

#include <atomic>

#include "UpdateQueue.h"
#include "../common_src/Thread.h"
#include "../enums/UpdateType.h"

class StatusUpdater : public Thread {
private:
	std::atomic<bool>& in_game; 
	UpdateQueue& update_queue;
	MenuStatus& menu_status; 
	GameStatusMonitor& game_status_monitor;
public:
	StatusUpdater(std::atomic<bool>& in_game, 
								UpdateQueue& update_queue,
								MenuStatus& menu_status, 
								GameStatusMonitor& game_status_monitor);
	~StatusUpdater();
	void run();
}

#endif