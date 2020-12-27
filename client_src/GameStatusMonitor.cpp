#include <iostream>

#include "GameStatusMonitor.h"

GameStatusMonitor::GameStatusMonitor() : synchronized(false) { }

GameStatusMonitor::~GameStatusMonitor() { }

void GameStatusMonitor::initializeGameStatus(Map& map, 
																						 GameStatusUpdate& update) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->game_status.initialize(map, update);
	this->synchronized = true;
	this->cv.notify_one();
}

void GameStatusMonitor::updateGameStatus(GameStatusUpdate& status_update) {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (this->synchronized) this->cv.wait(lock);
	this->game_status.update(status_update);
	this->synchronized = true;
	this->cv.notify_one();
}

GameStatusUpdate GameStatusMonitor::getUpdate() {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (!this->synchronized) this->cv.wait(lock);
	GameStatusUpdate update = this->game_status.getUpdate();
	this->synchronized = false;
	this->cv.notify_one();
	return update;
}

Map& GameStatusMonitor::getMap() {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (!this->synchronized) this->cv.wait(lock);
	this->synchronized = false;
	this->cv.notify_one();
	return this->game_status.getMap();
}
