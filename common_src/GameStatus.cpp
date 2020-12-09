#include "GameStatus.h"


GameStatus::GameStatus() {
	MapData md("map-data.yml");
	Map m(md);
	
	this->map = m;
	
	}
GameStatus::~GameStatus() {}


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
}

float GameStatus::getAngle(int playerID) {
    return this->playersDirections[playerID].getAngle();
}

bool GameStatus::isValidMovement(Vector &position){
    int x = (int)position.getXCoordinate();
    int y = (int)position.getYCoordinate();
    //return this->map.isWall(x,y);
    return true;
}
