#include "GameStatus.h"

GameStatus::GameStatus() : running(false) { }

GameStatus::~GameStatus() { }

void GameStatus::initialize(Map& new_map, GameStatusUpdate& status_update) {
	this->map = map;
	this->update(status_update);
}

void GameStatus::update(GameStatusUpdate& status_update) {
	PlayerStatus new_player_status { status_update.player_position,
																	 status_update.player_health,
																	 status_update.player_weapon,
																	 status_update.player_ammo,
																	 status_update.player_angle };
	this->player_status = new_player_status;
	this->running = status_update.running;
}

Map& GameStatus::getMap() {
	return this->map;
}

GameStatusUpdate GameStatus::getUpdate() {
	GameStatusUpdate update { this->player_status.position,
														this->player_status.health,
														this->player_status.current_weapon,
														this->player_status.current_weapon_ammo,
														this->player_status.angle,
														this->running };

	return update;
}

bool GameStatus::isRunning() {
	return this->running;
}