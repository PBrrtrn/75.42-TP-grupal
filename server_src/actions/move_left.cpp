#include "action.h"
#include "move_left.h"
#include "server.h"

#include <iostream>

MoveLeft::MoveLeft() {}

void MoveLeft::tryAction(Server &server, int clientID){
    server.tryMoveLeft(clientID);
}

MoveLeft::~MoveLeft() {}