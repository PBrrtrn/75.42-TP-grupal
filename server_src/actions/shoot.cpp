#include "action.h"
#include "shoot.h"
#include "server.h"

#include <iostream>

Shoot::Shoot(){}

void Shoot::tryAction(Server &server, int clientID){
    server.tryShoot(clientID);
}

Shoot::~Shoot() {}