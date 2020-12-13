#include "action.h"
#include "move_left.h"
#include "server.h"

#include <iostream>

MoveLeft::MoveLeft(int clientID) : Action(clientID) {}

void MoveLeft::tryAction(Server &server){
    server.tryMoveLeft(this->clientID);
}

MoveLeft::~MoveLeft() {}