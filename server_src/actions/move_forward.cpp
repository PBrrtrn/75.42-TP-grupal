#include "action.h"
#include "move_forward.h"

#include <iostream>

MoveForward::MoveForward() {}

void MoveForward::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
	Vector angle = gs.getAngle(clientID);
    angle.turnUnitary();
    Vector next_position = pos + (angle * STEP);
    is_colision(clientID, next_position, gs);
    
}

MoveForward::~MoveForward() {}
