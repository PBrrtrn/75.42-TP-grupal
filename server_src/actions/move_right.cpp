#include "action.h"
#include "move_right.h"

#include <iostream>

MoveRight::MoveRight(){}

void MoveRight::tryAction(GameStatus& gs, int clientID){
    if (!gs.players.at(clientID).outGame()) {
        Vector pos = gs.getPosition(clientID);
        float angle = gs.getAngle(clientID);
        angle += this->rotation_right;
        gs.setAngle(clientID, angle);
    }
}

MoveRight::~MoveRight() {}
