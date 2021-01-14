#include "game_manager.h"

GameManager::GameManager(){
	this->clients_counter = 0;
	//this->messages.push("a");
}

GameManager::~GameManager(){

    for (auto x: clientsThreads) {
        x.second->join();
        delete x.second;
    }
	
}

void GameManager::pushMessage(std::string m){

    std::cout << m << std::endl;
	
}

void GameManager::acceptClient(std::string socket, BlockingQueue<std::string>& q){
	std::cout << "Game manager accepted new Client (mock!)" << std::endl;
    this->clientsThreads.insert({this->clients_counter, 
		//new ThreadClient(this, this->clients_counter, messages)});
		new ThreadClient(this->clients_counter, q)});
    this->clientsThreads.at(this->clients_counter)->start();
    this->clients_counter++; 
    
}


