#include "action.h"
#include "move_right.h"

#include <iostream>

MoveRight::MoveRight(){}

void MoveRight::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
	float angle = gs.getAngle(clientID);
    angle += ROTATION_RIGHT;
    Vector next_position = pos + (angle * STEP);
    if (!is_colision(clientID, next_position, gs)) {
        gs.setAngle(clientID, angle);
    }
}

MoveRight::~MoveRight() {}
