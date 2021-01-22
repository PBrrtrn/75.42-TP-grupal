#include "game_status.h"

GameStatus::GameStatus(std::string mapLocation) {
	MapData md(mapLocation);
	Map m(md);
	this->map = m;
	
	Vector v(2,3); //removeme
	Item i(v); //removeme
	this->items.push_back(i); //removeme
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
		std::cout << "leyendo el unico item que tiene el gs, posx "<< item.getPosition().getXCoordinate() << std::endl;
        //int item_id = it.first;

        for (auto& player: this->players){
			//key: player.first;
			//valor: player.second;
			
			//comparar distancia de posicion item - posicion player
			// si la norma es menor a X AND item.canBePickedUp(), item.pickUp();
			
		}
        
    }
}

GameStatus::~GameStatus() {}
