#include "game_manager.h"

GameManager::GameManager() : serverStatus(this->games_list){
	std::cout << "game manager constructor"  << std::endl;
	this->clients_counter = 0;
    this->games_counter = 0;
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

    case TYPE_REFRESH_GAMES_LIST:
        this->informAvailableGames(message.getClientId());
        break;
    
    /*si el cliente mando un mensaje que esta asociado al juego donde 
     * esta jugando*/
    default:
        int gameId = this->clientsInGames.at(message.getClientId());
		this->queues.at(gameId)->push(message);	
        break;
    }
}

void GameManager::startGame(int clientIdStarter) {
	BlockingQueue<Message>* queue = new BlockingQueue<Message>();
    
	this->games.insert({ this->games_counter, new ThreadGame(this->games_counter, queue, this->games_list) });
	this->clientsInGames.insert({clientIdStarter,this->games_counter});

	this->queues.insert(std::make_pair(this->games_counter, queue));

	std::cout << "id de cliente arrancando juego:" << clientIdStarter << std::endl;

	this->games.at(this->games_counter)->addClient(this->clientsThreads.at(clientIdStarter), clientIdStarter);
	this->games.at(this->games_counter)->start();
	this->games_counter++;
}

void GameManager::joinGame(int clientId, int gameId) {
    
    if (this->games.at(gameId)->addClient(this->clientsThreads.at(clientId), clientId)) {
		this->clientsInGames.insert({clientId, gameId});
	}
}

void GameManager::acceptClient(Socket&& socket, BlockingQueue<Message>& qClientsProcessor){
	std::cout << "Game manager accepted new Client:"<< this->clients_counter << std::endl;
	
	int clientId = this->clients_counter;
	this->out_queues.insert({clientId, new BlockingQueue<Message>()} );

    this->clientsThreads.insert({this->clients_counter, 
        new ThreadClient(this->clients_counter, qClientsProcessor , 
        this->out_queues.at(this->clients_counter), std::move(socket), this->serverStatus)});
    
    this->clientsThreads.at(this->clients_counter)->start();

    this->clients_counter++;
}

void GameManager::informAvailableGames(int clientId){
	this->out_queues.at(clientId)->push(Message(TYPE_SERVER_SEND_GAMES_LIST,0,clientId));
}

void GameManager::cleanUpDeadGames(){
	for (auto x: this->games) {
        if (x.second->isDead()) {
            x.second->join();
            delete x.second;
            this->games.erase(x.first);
        }
    }
}

GameManager::~GameManager(){
    for (auto x: this->clientsThreads) {
        x.second->shutdown();
        x.second->join();
        delete x.second;
    }
    for (auto x: this->games) {
        x.second->shutdown();
        x.second->join();
        delete x.second;
    }
    for (auto x: this->queues) {
        delete x.second;
    }
    for (auto x: this->out_queues) {
        delete x.second;
    }
}
