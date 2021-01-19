#include "game_manager.h"

GameManager::GameManager(){
	std::cout << "game manager constructor"  << std::endl;
	this->clients_counter = 0;
    this->games_counter = 0;
}

GameManager::~GameManager(){
    for (auto x: clientsThreads) {
        x.second->join();
        delete x.second;
    }
}

void GameManager:: newMessage(Message message) {
    this->_parse_message(message);
}

void GameManager:: _parse_message(Message message) {
    switch (message.getType())
    {
    case TYPE_START_GAME:
        this->startGame(message.getClientId());
        break;
    
    case TYPE_JOIN_GAME:
        this->joinGame(message.getClientId(), message.getEntity());
        break;
    
    default:
        int gameId = this->clientsInGames.at(message.getClientId());
		this->queues.at(gameId)->push(message);	
        break;
    }
}

void GameManager::startGame(int clientIdStarter) {
	BlockingQueue<Message>* queue = new BlockingQueue<Message>();
    
    
	this->games.insert({ this->games_counter, new ThreadGame(this->games_counter, queue) });
	this->clientsInGames.insert({clientIdStarter,this->games_counter});

	this->queues.insert(std::make_pair(this->games_counter, queue));

	std::cout << "id de cliente arrancando juego:" << clientIdStarter << std::endl;

	this->games.at(this->games_counter)->addClient(this->clientsThreads.at(clientIdStarter), clientIdStarter);
	this->games.at(this->games_counter)->start(); //arranca th game
	this->games_counter++;
}

void GameManager::joinGame(int clientId, int gameId) {
    this->clientsInGames.insert({clientId, gameId});
    this->games.at(gameId)->addClient(this->clientsThreads.at(clientId), clientId);
}

void GameManager::acceptClient(std::string socket, BlockingQueue<Message>& q){
	std::cout << "Game manager accepted new Client:"<< this->clients_counter << std::endl;

    //BlockingQueue<GameStatus>* queue_out = new BlockingQueue<GameStatus>();
    //this->out_queues.insert(std::make_pair(this->clients_counter, queue_out));

    this->clientsThreads.insert({this->clients_counter, 
        //new ThreadClient(this->clients_counter, q, *queue_out)});
        new ThreadClient(this->clients_counter, q )});
    this->clientsThreads.at(this->clients_counter)->start();
    this->clients_counter++;
}

void GameManager:: updateClients() {
    for (auto& it: this->out_queues) {
        int clientId = it.first;
        int gameId = this->clientsInGames.at(it.first);
        //TODO: chequear tiempo de ejecucion -- eficiencia pasaje gamestatus
        this->out_queues.at(clientId)->push(this->games.at(gameId)->getGameStatus());
    }
}

void GameManager::cleanUpDeadGames(){
	//recorrer this->games y si game.isDead, join() y eliminar
}
