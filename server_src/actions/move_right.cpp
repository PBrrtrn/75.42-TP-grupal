#include "action.h"
#include "move_right.h"

#include <iostream>

MoveRight::MoveRight(){}

void MoveRight::tryAction(GameStatus& gs, int clientID){
    Vector pos = gs.getPosition(clientID);
    float angle = gs.getAngle(clientID);
    angle += this->rotation_right;
    gs.setAngle(clientID, angle);
    std::cout << angle << std::endl;
}

MoveRight::~MoveRight() {}
