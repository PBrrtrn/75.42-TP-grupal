#include "game_status.h"

GameStatus::GameStatus(std::string mapLocation) {
	MapData md(mapLocation);
	Map m(md);
	this->map = m;

	/***************** REMOVE ************************************/
	Vector v(2,3); //removeme
	Item i(v,true); //removeme
	this->items.push_back(i); //removeme

	Vector v2(2,3); //removeme
	ArmaAmetralladora a(v2,true); //removeme
	this->items.push_back(i); //removeme
	/***************** REMOVE ************************************/

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
			if (abs(distance.calculateNorma()) < 1 && item.canBePickedUp()) {
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

void GameStatus::respawnItems(){
	for (auto& it: this->items){
		Item& item = it;
		item.tick();
	}
}

GameStatus::~GameStatus() {}
