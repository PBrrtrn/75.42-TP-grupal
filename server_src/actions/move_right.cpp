#include "action.h"
#include "move_left.h"
#include "server.h"

#include <iostream>

MoveRight::MoveRight(){}

void MoveRight::tryAction(Server &server, int clientID){
    server.tryMoveRight(clientID);
}

MoveRight::~MoveRight() {}