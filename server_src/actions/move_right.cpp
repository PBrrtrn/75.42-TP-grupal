#include "action.h"
#include "move_right.h"

#include <iostream>

MoveRight::MoveRight(){}

void MoveRight::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
	float angle = gs.getAngle(clientID);
    angle += this->rotation_right;
    //Vector next_position = pos + (angle * this->step);
    //if (!is_colision(clientID, next_position, gs)) {
        gs.setAngle(clientID, angle);
    //}
}

MoveRight::~MoveRight() {}
