#include "action.h"
#include "move_left.h"

#include <iostream>

MoveLeft::MoveLeft() {}

void MoveLeft::tryAction(GameStatus& gs, int clientID, Map& map){
    Vector pos = gs.getPosition(clientID);
	float angle = gs.getAngle(clientID);
    angle += ROTATION_LEFT;
    Vector next_position = pos + (angle * STEP);
    if (!is_colision(clientID, next_position, map, gs)) {
        gs.setAngle(clientID, angle);
    }
}

MoveLeft::~MoveLeft() {}