#include "server.h"
#include <iostream>

Server::Server() {}

void Server::start() {
    std::cout << "SERVER STARTED." << std::endl;
    this->acceptor.start();
    
    std::string line;
    while (std::getline(std::cin, line)) {
		if (line == "q" || line == "quit") break;
	}
	
	this->acceptor.shutdown();
}


Server::~Server(){
    this->acceptor.join();
}
