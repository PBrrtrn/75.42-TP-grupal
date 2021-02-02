#ifndef __UPDATE_QUEUE_H__
#define __UPDATE_QUEUE_H__

#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

#include "../enums/UpdateType.h"

class UpdateQueue {
private:
	std::mutex mutex;
	std::condition_variable cv;
	std::queue<UpdateType> queue;
public:
	UpdateQueue();
	~UpdateQueue();
	void pushUpdate(UpdateType update);
	UpdateType popUpdate();
};

#endif