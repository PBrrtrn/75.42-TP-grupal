#include "action.h"
#include "shoot.h"
#include "server.h"

#include <iostream>

Shoot::Shoot(int clientID) : Action(clientID) {}

void Shoot::tryAction(Server &server){
    server.tryShoot(this->clientID);
}

Shoot::~Shoot() {}