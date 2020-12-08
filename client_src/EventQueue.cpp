#include "EventQueue.h"

EventQueue::EventQueue() { }

EventQueue::~EventQueue() { }

void EventQueue::add(int event) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->queue.push(event);
	this->cv.notify_all();
}

int EventQueue::pop() {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (queue.empty()) {
		this->cv.wait(lock);
	}
	int event = queue.front();
	queue.pop();
	return event;
}