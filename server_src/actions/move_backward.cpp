#include "action.h"
#include "move_backward.h"

#include <iostream>

MoveBackward::MoveBackward() {}

void MoveBackward::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
	Vector angle = gs.getAngle(clientID);
    angle.turnUnitary();
    Vector next_position = pos - (angle * STEP);
    is_colision(clientID, next_position, gs);
}

MoveBackward::~MoveBackward() {}
