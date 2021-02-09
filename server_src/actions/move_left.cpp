#include "action.h"
#include "move_left.h"

#include <iostream>

MoveLeft::MoveLeft() {}

void MoveLeft::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
		float angle = gs.getAngle(clientID);
    angle += this->rotation_left;
    gs.setAngle(clientID, angle);
    std::cout << angle << std::endl;
}

MoveLeft::~MoveLeft() {}
