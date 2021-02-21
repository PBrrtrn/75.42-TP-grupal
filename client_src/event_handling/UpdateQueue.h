#ifndef __UPDATE_QUEUE_H__
#define __UPDATE_QUEUE_H__

#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

#include "../../common_src/MessageType.h"

class EventQueue {
private:
	std::mutex mutex;
	std::condition_variable cv;
	std::queue<MessageType> queue;
public:
	EventQueue();
	~EventQueue();
	void push(MessageType event);
	MessageType pop();
};

#endif