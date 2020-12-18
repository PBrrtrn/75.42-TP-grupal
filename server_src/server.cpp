#include "server.h"
#include "vector.h"
#include <iostream>

Server::Server() {}

void Server:: start() {
    this->acceptor = new ThreadAcceptor(/*this->socket*/);
    this->acceptor->start();
}

/*
bool Server:: ready_to_receive() {
    return this->socket.socket_bind_and_listen(NULL, this->server_port);
}
*/

Server::~Server(){
    this->acceptor->stop();
    this->acceptor->join();
    delete this->acceptor;
}
