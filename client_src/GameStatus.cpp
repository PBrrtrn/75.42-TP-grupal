#include "GameStatus.h"

GameStatus::GameStatus() { }

GameStatus::~GameStatus() { }

GameStatus::initialize(Map& new_map, GameStatusUpdate& status_update) {
	this->map = map;
	this->update(status_update);
}

GameStatus::update(GameStatusUpdate& status_update) {
	this->player_status { status_update.player_position,
												status_update.player_health,
												status_update.player_weapon,
												status_update.current_weapon_ammo };
}
