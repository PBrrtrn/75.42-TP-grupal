#include "game_manager.h"

GameManager::GameManager(){
	
}

GameManager::~GameManager(){

    for (auto x: clientsThreads) {
        x.second->join();
        delete x.second;
    }
	
}

void GameManager::acceptClient(std::string socket){
	std::cout << "Game manager accepted new Client (mock!)" << std::endl;
    this->clientsThreads.insert({this->clients_counter, 
		new ThreadClient(this, this->clients_counter, messages)});
    this->clientsThreads.at(this->clients_counter)->start();
    this->clients_counter++; 
    
}


