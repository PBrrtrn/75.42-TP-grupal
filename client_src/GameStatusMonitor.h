#ifndef __GAME_STATUS_MONITOR_H__
#define __GAME_STATUS_MONITOR_H__

#include <mutex>
#include <atomic>
#include <condition_variable>

#include "GameStatus.h"

class GameStatusMonitor {
private:
	GameStatus game_status;
	std::mutex mutex;
	std::condition_variable cv;
	std::atomic<bool> synchronized;
	void apply(GameStatusUpdate& update);
public:
	GameStatusMonitor();
	~GameStatusMonitor();
	initializeGameStatus(Map& map, GameStatusUpdate& update);
	void updateGameStatus(GameStatusUpdate& update);
	GameStatus& getCurrentGameStatus();
};

#endif