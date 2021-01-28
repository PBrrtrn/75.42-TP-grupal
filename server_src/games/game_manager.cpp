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

    case TYPE_REFRESH_GAMES_LIST:
        this->informAvailableGames(); //TODO ver a quién mandarle el refresh -- por socket
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

void GameManager::acceptClient(Socket& socket, BlockingQueue<Message>& q){
	std::cout << "Game manager accepted new Client:"<< this->clients_counter << std::endl;

    this->clientsThreads.insert({this->clients_counter, 
        new ThreadClient(this->clients_counter, q )});
    this->clientsThreads.at(this->clients_counter)->start();
    //std::string client_id;
    //client_id = std::to_string(this->clients_counter);
    char client_id = (char)this->clients_counter;
    //socket.socket_send(client_id.c_str(), strlen(client_id.c_str()));
    socket.socket_send(&client_id, sizeof(char));
    this->clientsSockets.insert({this->clients_counter, Socket(std::move(socket))});
    this->clients_counter++;
}

void GameManager::informAvailableGames(){
	AvailableGames a = this->getAvailableGames();
	//busco los clientes que NO estan en un game actualmente
	for (auto& it: this->clientsThreads) {
		if (this->clientsInGames.find(it.first) == this->clientsInGames.end()) {
			//this->clientsSockets.send(a);
		}
	}
	
}
// TODO: Implementar devolucion de estructura AvailableGames
AvailableGames GameManager::getAvailableGames(){ 
	AvailableGames a;
	return a;
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
