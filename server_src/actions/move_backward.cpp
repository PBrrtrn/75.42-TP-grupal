#include "action.h"
#include "move_backward.h"

#include <iostream>

MoveBackward::MoveBackward() {}

void MoveBackward::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
	Vector direction = gs.getDirection(clientID);
    direction.turnUnitary();
    Vector next_position = pos - (direction * this->step);
    is_colision(clientID, next_position, gs);
}

MoveBackward::~MoveBackward() {}
