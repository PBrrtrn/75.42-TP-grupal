#include "game_manager.h"

GameManager::GameManager(){
	this->messages.push("a");
    /*this->messages.push("s");
    this->messages.push("d");
    this->messages.push("a");
    this->messages.push("s");
    this->messages.push("w");*/
    //this->game.start();
}

void GameManager::acceptClient(std::string socket){
	std::cout << "Game manager accepted new Client (mock!)" << std::endl;
    this->clientsThreads.insert({this->clients_counter, 
		new ThreadClient(this, this->clients_counter, messages)});
    this->clientsThreads.at(this->clients_counter)->start();
    this->game.addClient(this->clientsThreads.at(this->clients_counter), this->clients_counter);
    this->clients_counter++;
}

void GameManager:: newMessage(std::string message, int clientID) {
    this->_parse_message(message, clientID); //por ahora cout msg
    //if action == new game
    //new th_game(id client)
    //else gameclient(action)
}

/*
void GameManager:: _parse_message(std::string message, int clientID) {
    if (message == "w") {
        this->games.at(clientID)->tryMoveForward(clientID);
    } else if (message == "a") {
        this->games.at(clientID)->tryMoveLeft(clientID);
    } else if (message == "d") {
        this->games.at(clientID)->tryMoveRight(clientID);
    } else if (message == "s") {
        this->games.at(clientID)->tryMoveBackward(clientID);
    }
}
*/

void GameManager:: _parse_message(std::string message, int clientID) {
    if (message == "w") {
        this->game.tryMoveForward(clientID);
    } else if (message == "a") {
        this->game.tryMoveLeft(clientID);
    } else if (message == "d") {
        this->game.tryMoveRight(clientID);
    } else if (message == "s") {
        this->game.tryMoveBackward(clientID);
    }
}

GameManager::~GameManager(){
    for (auto x: clientsThreads) {
        x.second->join();
        delete x.second;
    }
    //this->game.join();
}
