#include "UpdateQueue.h"

UpdateQueue::UpdateQueue() { }

UpdateQueue::~UpdateQueue() { }

void UpdateQueue::pushUpdate(UpdateType update) {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (!this->queue.empty()) this->cv.wait(lock);

	queue.push(update);
}

UpdateType UpdateQueue::popUpdate() {
	std::unique_lock<std::mutex> lock(this->mutex);

	UpdateType update = MENU_NONE;
	if (!this->queue.empty()) {
		update = this->queue.front();
		this->queue.pop();
	}

	return update;
}
