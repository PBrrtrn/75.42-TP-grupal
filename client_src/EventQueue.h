#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>

class EventQueue {
private:
	std::mutex mutex;
	std::queue<int> queue;
	std::condition_variable cv;
public:
	EventQueue();
	~EventQueue();
	void add(int event); // TODO: Definir el enum event
	int pop();
};

#endif