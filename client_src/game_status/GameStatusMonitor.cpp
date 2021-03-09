#include <iostream>

#include "GameStatusMonitor.h"

GameStatusMonitor::GameStatusMonitor() 
: synchronized(false), map_initialized(false), statistics_saved(false) { }

GameStatusMonitor::~GameStatusMonitor() { }

void GameStatusMonitor::initializeMap(Map& map) {
  std::unique_lock<std::mutex> lock(this->mutex);
  this->game_status.initialize(map);
  this->map_initialized = true;
  this->cv.notify_one();
}

Map& GameStatusMonitor::getMap() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (!this->map_initialized) this->cv.wait(lock);
  return this->game_status.getMap();
}

void GameStatusMonitor::saveStatistics(GameStatistics& statistics) {
  std::unique_lock<std::mutex> lock(this->mutex);
  this->game_status.saveStatistics(statistics);
  this->statistics_saved = true;
  this->cv.notify_one();
}

GameStatistics& GameStatusMonitor::getStatistics() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (!this->statistics_saved) this->cv.wait(lock);
  return this->game_status.getStatistics();
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
