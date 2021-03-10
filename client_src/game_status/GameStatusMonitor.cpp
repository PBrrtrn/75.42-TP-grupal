#include <iostream>

#include "GameStatusMonitor.h"

GameStatusMonitor::GameStatusMonitor() 
: synchronized(false), map_initialized(false), open(true) { }

GameStatusMonitor::~GameStatusMonitor() {
  this->open = false;
}

void GameStatusMonitor::initializeMap(Map& map) {
  std::unique_lock<std::mutex> lock(this->mutex);
  this->game_status.initialize(map);
  this->map_initialized = true;
  this->cv.notify_one();
}

Map& GameStatusMonitor::getMap() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (!this->map_initialized) this->cv.wait(lock);
  if (!this->open) throw ClosedGameStatusMonitor();
  return this->game_status.getMap();
}

void GameStatusMonitor::updateGameStatus(GameStatusUpdate& status_update) {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (this->synchronized) this->cv.wait(lock);
  if (!this->open) throw ClosedGameStatusMonitor();
  this->game_status.update(status_update);
  this->synchronized = true;
  this->cv.notify_one();
}

GameStatusUpdate GameStatusMonitor::getUpdate() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (!this->synchronized) this->cv.wait(lock);
  if (!this->open) throw ClosedGameStatusMonitor();
  GameStatusUpdate update = this->game_status.getUpdate();
  this->synchronized = false;
  this->cv.notify_one();
  return update;
}

void GameStatusMonitor::endGame() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (this->synchronized) this->cv.wait(lock);
  if (!this->open) throw ClosedGameStatusMonitor();
  this->synchronized = true;
  this->cv.notify_one();
}

void GameStatusMonitor::close() {
  this->open = false;
  this->cv.notify_one();
}