#include "action.h"
#include "server.h"
#include <iostream>

Action::Action(int clientID) : clientID(clientID){}

void Action::tryAction(Server &server) {}

Action::~Action() {}
