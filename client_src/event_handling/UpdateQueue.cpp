#include "UpdateQueue.h"

UpdateQueue::UpdateQueue() { }

UpdateQueue::~UpdateQueue() { }

void UpdateQueue::pushUpdate(UpdateType update) {
	std::unique_lock<std::mutex> lock(this->mutex);
	queue.push(update);
	this->cv.notify_one();
}

UpdateType UpdateQueue::popUpdate() {
	std::unique_lock<std::mutex> lock(this->mutex);

	while (this->queue.empty()) this->cv.wait(lock);
	UpdateType update = this->queue.front();
	this->queue.pop();

	return update;
}
