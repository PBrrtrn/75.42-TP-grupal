#include "SpawnPoint.h"

SpawnPoint::SpawnPoint(Vector position,Vector direction) :
	position(position),direction(direction) {}

Vector SpawnPoint::getPosition() {
	return this->position;
}

Vector SpawnPoint::getDirection() {
	return this->direction;
}

SpawnPoint::~SpawnPoint() {}
