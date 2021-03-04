#include "server.h"
#include <iostream>

Server::Server() {}

void Server::start() {
    std::cout << "SERVER STARTED." << std::endl;
    this->acceptor.start();

    std::string line;
    while (true) {
        std::getline(std::cin, line);
		if (line == "q" || line == "quit") {
           	this->acceptor.shutdown(); 
            return;
        }
	}
}


Server::~Server(){
    this->acceptor.join();
}
