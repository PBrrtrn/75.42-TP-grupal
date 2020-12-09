//
// Created by alejo on 29/11/20.
//

#include "ThreadClient.h"
#include "Client.h"
#include "Server.h"

ThreadClient::ThreadClient(Server &server) : server(server) {}

void ThreadClient::run() {
    Client client(this->server);
}

ThreadClient::~ThreadClient(){}
