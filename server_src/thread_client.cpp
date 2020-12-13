#include "thread_client.h"
#include "server.h"

ThreadClient::ThreadClient(Server &server) : server(server) {}

void ThreadClient::run() {
    Client client(this->server);
}

ThreadClient::~ThreadClient(){}
