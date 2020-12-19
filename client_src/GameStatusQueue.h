#ifndef __GAME_STATUS_QUEUE_H__
#define __GAME_STATUS_QUEUE_H__

#include <mutex>
#include <atomic>
#include <condition_variable>

#include "GameStatus.h"

class GameStatusQueue {
private:
	std::mutex mutex;
	std::condition_variable cv;
	GameStatus game_status;
	std::atomic<bool> synchronized;
public:
	GameStatusQueue();
	~GameStatusQueue();
	void updateGameStatus(GameStatus new_game_status);
	GameStatus& getCurrentGameStatus();
};

#endif