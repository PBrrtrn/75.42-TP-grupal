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


void GameManager:: newMessage(Message message) {
    this->_parse_message(message); //por ahora cout msg
    //if action == new game
    //new th_game(id client)
    //else gameclient(action)
}


void GameManager:: _parse_message(Message message) {
	
	if (message.getMessage() == "n") {
		this->startGame(message.getClientId());
		
	} else {
		int gameId = this->clientsInGames.at(message.getClientId());
		this->queues.at(gameId)->push(message);		
	}

	
    /*if (message.getMessage() == "w") {
        this->games.at(gameId)->tryMoveForward(message.getClientId());
    } else if (message.getMessage() == "a") {
        this->games.at(gameId)->tryMoveLeft(message.getClientId());
    } else if (message.getMessage() == "d") {
        this->games.at(gameId)->tryMoveRight(message.getClientId());
    } else if (message.getMessage() == "s") {
        this->games.at(gameId)->tryMoveBackward(message.getClientId());
    }*/
}

void GameManager::startGame(int clientIdStarter){
	
	BlockingQueue<Message>* queue = new BlockingQueue<Message>();
	this->games.insert({ this->games_counter, new ThreadGame(this->games_counter,queue) });
	this->clientsInGames.insert({clientIdStarter,this->games_counter});
	this->queues.insert(std::make_pair(this->games_counter, queue));
	
	this->games.at(this->games_counter)->start();
	
	this->games_counter++;
	
	
	
}

void GameManager::acceptClient(std::string socket, BlockingQueue<Message>& q){
	std::cout << "Game manager accepted new Client (mock!)" << std::endl;
    this->clientsThreads.insert({this->clients_counter, 
		new ThreadClient(this->clients_counter, q)});
    this->clientsThreads.at(this->clients_counter)->start();
    this->clients_counter++; 
    
    
    
}


