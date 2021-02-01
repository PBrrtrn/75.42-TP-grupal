#include "game_status.h"

GameStatus::GameStatus(std::string mapLocation) {
	this->map = Map(mapLocation);
}

void GameStatus::setPosition(int playerID, float pos_x, float pos_y) {
    this->playersPositions[playerID] = Vector(pos_x, pos_y);
}

void GameStatus::setPosition(int playerID, Vector &playerPosition) {
    this->playersPositions[playerID] = playerPosition;
}

void GameStatus::setAngle(int playerID, float angle) {
	this->playersDirections[playerID] = Vector(angle);
}

Vector GameStatus::getPosition(int playerID) {
	return this->playersPositions[playerID];
}

void GameStatus::addPlayer(int playerID, Vector &position, Vector &direction) {
    this->playersPositions[playerID] = position;
    this->playersDirections[playerID] = direction;

    Player jugador(playerID);
	this->players.insert({playerID, jugador});
}

float GameStatus::getAngle(int playerID) {
    return this->playersDirections[playerID].getAngle();
}

void GameStatus::checkPlayerPickups(){
	for (auto& item: this->items) {
		Vector item_position = item.getPosition();

        for (auto& it: this->players){
			int player_id = it.first;
			Player player = it.second;

			Vector distance = item_position - this->getPosition(player_id);
			if (abs(distance.norm()) < 1 && item.canBePickedUp()) {
				item.pickUp(player);
			}			
		}
        
    }
}

void GameStatus::checkPlayerBullets(){
	for (auto& it: this->players){
		int player_id = it.first;
		Player& player = it.second;

		if (player.getCurrentBullets() == 0) {
			player.changeWeapon(0);
		}		
	}	
	
}

int GameStatus::getAlivePlayers() {
	int amount_alive = 0;
	for (auto& it: this->players){
		int player_id = it.first;
		Player& player = it.second;
		if (!player.is_dead()) amount_alive++;
	}	
	return amount_alive;
}

Statistics GameStatus::showStatistics() {
	for (auto& it: this->players){
		int player_id = it.first;
		Player& player = it.second;
		this->statistics.addPointsTreasure(player_id, player.getPoints());	
	}	
	return this->statistics;
}

void GameStatus::addEnemyDead(int playerID) {
	this->statistics.addEnemyDead(playerID);
}

void GameStatus::addBulletShooted(int playerID) {
	this->statistics.addBulletShooted(playerID);
}

void GameStatus::respawnItems(){
	for (auto& it: this->items){
		Item& item = it;
		item.tick();
	}
}

GameStatus::~GameStatus() {}
