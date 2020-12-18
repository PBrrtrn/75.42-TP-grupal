#include "action.h"
#include "move_backward.h"
#include "server.h"

#include <iostream>

MoveBackward::MoveBackward() {}

void MoveBackward::tryAction(Server &server, int clientID){
    server.tryMoveBackward(clientID);
}

MoveBackward::~MoveBackward() {}