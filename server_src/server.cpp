#include "server.h"
#include "vector.h"
#include <iostream>

Server::Server() {}

void Server:: start() {
    std::cout << "SERVER STARTED." << std::endl;
    //TODO mensajes inicio juego
    /*
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "q" || line == "quit") break;
    }
    */
    this->acceptor = new ThreadAcceptor(/*this->socket*/);
    this->acceptor->start();
}

/*
bool Server:: ready_to_receive() {
    return this->socket.socket_bind_and_listen(NULL, this->server_port);
}
*/

Server::~Server(){
    //this->acceptor->stop();
    this->acceptor->join();
    delete this->acceptor;
}
