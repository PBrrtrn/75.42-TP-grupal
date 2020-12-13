#include "action.h"
#include "move_backward.h"
#include "server.h"

#include <iostream>

MoveBackward::MoveBackward(int clientID) : Action(clientID) {}

void MoveBackward::tryAction(Server &server){
    server.tryMoveBackward(this->clientID);
}

MoveBackward::~MoveBackward() {}