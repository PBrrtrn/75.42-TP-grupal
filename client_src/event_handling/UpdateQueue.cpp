#include "UpdateQueue.h"

UpdateQueue::UpdateQueue() { }

UpdateQueue::~UpdateQueue() { }

UpdateQueue::pushUpdate(Update update) {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (!this->queue.empty()) this->cv.wait(lock);

	queue.push(update);
}

Update UpdateQueue::popUpdate() {
	std::unique_lock<std::mutex> lock(this->mutex);

	Update update = MENU_NONE;
	if (!this->queue.empty()) {
		update = this->queue.front();
		this->queue.pop();
	}

	return update;
}
