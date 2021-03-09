#include <iostream>
#include "GameStatus.h"

GameStatus::GameStatus() { }

GameStatus::~GameStatus() { }

void GameStatus::initialize(Map new_map) {
  this->map = new_map;
}

void GameStatus::update(GameStatusUpdate& status_update) {
  PlayerStatus new_player_status { status_update.position,
                                   status_update.direction,
                                   status_update.selected_weapon,
                                   status_update.health,
                                   status_update.bullets,
                                   status_update.lives,
                                   status_update.has_key,
                                   status_update.player_firing };

  this->player_status = new_player_status;
  this->enemies = status_update.enemies;
  this->items = status_update.items;
}

Map& GameStatus::getMap() {
  return this->map;
}

GameStatusUpdate GameStatus::getUpdate() {
  GameStatusUpdate update { this->player_status.position,
                            this->player_status.direction,
                            this->player_status.selectedWeapon,
                            this->player_status.health,
                            this->player_status.bullets,
                            this->player_status.lives,
                            this->player_status.hasKey,
                            this->player_status.firing_state,
                            this->enemies,
                            this->items };

  return update;
}

void GameStatus::saveStatistics(GameStatistics& statistics) {
  this->statistics = statistics;
}

GameStatistics& GameStatus::getStatistics() {
  return this->statistics;
}

/*
bool GameStatus::isRunning() {
  return this->running;
}
*/
