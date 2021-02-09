#include "action.h"
#include "move_forward.h"

#include <iostream>

MoveForward::MoveForward() {}

void MoveForward::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
		Vector direction = gs.getDirection(clientID);
    direction.turnUnitary();
    Vector next_position = pos + (direction * this->step);
    is_colision(clientID, next_position, gs);
}

MoveForward::~MoveForward() {}
