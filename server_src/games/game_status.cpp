#include "game_status.h"

GameStatus::GameStatus(std::string mapLocation) {
	MapData md(mapLocation);
	Map m(md);
	this->map = m;
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

GameStatus::~GameStatus() {}
