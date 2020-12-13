#include "action.h"
#include "move_forward.h"
#include "server.h"

#include <iostream>

MoveForward::MoveForward(int clientID) : Action(clientID) {}

void MoveForward::tryAction(Server &server){
    server.tryMoveForward(this->clientID);
}

MoveForward::~MoveForward() {}