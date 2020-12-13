#include "action.h"
#include "move_left.h"
#include "server.h"

#include <iostream>

MoveRight::MoveRight(int clientID) : Action(clientID) {}

void MoveRight::tryAction(Server &server){
    server.tryMoveRight(this->clientID);
}

MoveRight::~MoveRight() {}