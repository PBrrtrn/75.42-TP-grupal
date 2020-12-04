#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <mutex>
#include <queue>

class BlockingQueue {
private:
	std::mutex mutex;
	std::queue queue;
public:
	BlockingQueue();
	~BlockingQueue();
}

#endif