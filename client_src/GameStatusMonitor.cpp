#include "GameStatusMonitor.h"

GameStatusMonitor::GameStatusMonitor() : synchronized(false) { }

GameStatusMonitor::~GameStatusMonitor() { }

void GameStatusMonitor::initializeGameStatus(Map map, 
																						 GameStatusUpdate& update) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->game_status.initialize(map, update);
	this->synchronized = true;
}

void GameStatusMonitor::updateGameStatus(GameStatusUpdate& status_update) {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (this->synchronized) this->cv.wait(lock);
	this->game_status.update(status_update);
	this->synchronized = true;
}

GameStatus& GameStatusMonitor::getCurrentGameStatus() {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (!this->synchronized) this->cv.wait(lock);
	this->synchronized = false;

	return this->game_status;
}
